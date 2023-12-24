
DIR=$(pwd);
BACKEND="${DIR}/backend"
TEMPLATE="${DIR}/backend/template"

DYNAMIC="${BACKEND}/src/dynamic_ssc"

show_help()
{
    echo -e "Usage: webserver [ARG]";
    echo -e "Dynamic C webframework\n";
    echo -e "-s, --start\tLoads config file and starts server";
    echo -e "-l, --load\tLoads config file without starting server";
    echo -e "-r, --restart\tLoads config file and restarts server";
    echo -e "-h, --help\tShows this menu";
}

if [ $# -eq 0 ]; then
    printf "Missing arguments\n\n";
    show_help;
    exit 0;
fi

quit()
{
    printf "%s\n" "${1}";
    exit 1;
}

check_dir()
{
    if [ ! -f "./config.h" ]; then
        quit "INVALID DIRECTORY: Cannot find config.h\n"
    fi

    if [ ! -d "./backend" ]; then
        quit "INVALID DIRECTORY: Cannot find backend\n"
    fi
}

# grep -En "^// ### AUTOMATIC INSERTION POINT ###" ./backend/src/dynamic_ssc/dynamic_ssc_loader.c | grep -Eo "^[0-9]+"
# sed '2a\hello'
# sed -rn "s/^void ([^\(]+)\(.*/\1/p" ./ssc/test.c

load_config()
{
    printf "Loading config.h\n";
    cp ./config.h ${BACKEND}/lib/config/;

    cp ${TEMPLATE}/template_dynamic_ssc_loader.c ${TEMPLATE}/dynamic_ssc_loader.c;
    INSERT_POINT=$(grep -En "^// ### AUTOMATIC INSERTION POINT ###" ${TEMPLATE}/dynamic_ssc_loader.c | grep -Eo "^[0-9]+");

    printf "Parsing ssc files\n";
    DYNAMIC_FUNCTIONS=$(find ./ssc/ -type f -name *.c | xargs -I {} sed -rn "s/^void ([^\(]+)\(.*/\1/p" {});
    IFS=$'\n';
    ARRAY=($DYNAMIC_FUNCTIONS);

    printf "Inserting dynamic functions\n";
    for FUNC in "${ARRAY[@]}"
    do
        APP="${INSERT_POINT}a\\index = hash_function(\"${FUNC}\");\nassert(dyn_function_hashmap[index] == NULL);\ndyn_function_hashmap[index] = ${FUNC};\n";
        sed ${APP} ${TEMPLATE}/dynamic_ssc_loader.c -i;
    done

    cp ${TEMPLATE}/template_dynamic_def.h ${TEMPLATE}/dynamic_def.h;
    INSERT_POINT=$(grep -En "^// ### AUTOMATIC INSERTION POINT ###" ${TEMPLATE}/dynamic_def.h | grep -Eo "^[0-9]+");
    for FUNC in "${ARRAY[@]}"
    do
        APP="${INSERT_POINT}a\\void ${FUNC}(FILE*,char*);\n";
        sed ${APP} ${TEMPLATE}/dynamic_def.h -i;
    done
    IFS=$' ';

    cp ${TEMPLATE}/template_dynamic_ssc_loader.h ${TEMPLATE}/dynamic_ssc_loader.h;
    DYNAMIC_FUNCTION_COUNT=$(sed -rn "s/static const int MAX_DYNAMIC_FUNCTIONS = ([0-9]+);/\1/p" ${BACKEND}/lib/config/config.h);
    sed s/MAX_DYNAMIC_FUNCTIONS/${DYNAMIC_FUNCTION_COUNT}/ ${TEMPLATE}/dynamic_ssc_loader.h -i;

    cp ${TEMPLATE}/dynamic_def.h ${BACKEND}/lib/dynamic_ssc/;
    cp ${TEMPLATE}/dynamic_ssc_loader.c ${BACKEND}/src/dynamic_ssc/;
    cp ${TEMPLATE}/dynamic_ssc_loader.h ${BACKEND}/lib/dynamic_ssc/;

    rm ${TEMPLATE}/dynamic_def.h;
    rm ${TEMPLATE}/dynamic_ssc_loader.c;
    rm ${TEMPLATE}/dynamic_ssc_loader.h;

    printf "Dynamic functions loaded\n";
}

start_server()
{
    printf "Starting server...\n";
    load_config;
    cd ${BACKEND};
    make release build;
    cd ${DIR};
    ./backend/bin/main;
}

check_dir;

case ${1} in
    "-s")
        start_server;
        ;;
    "--start")
        start_server;
        ;;
    "-l")
        load_config;
        ;;
    "--load")
        load_config;
        ;;
    "-h")
        show_help;
        ;;
    "--help")
        show_help;
        ;;
esac

