#idf_component_register(SRCS "main.c"
#                    INCLUDE_DIRS ".")
# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS  "main.c"
                    "queuesApp.c"
                    "wifiStation.c"
                    "ledTask.c"
                    "tcpServerTask.c"     
                    "flashTask.c"           
                    "json/value.c"
                    "json/hashtable.c"
                    "json/memory.c"
                    "json/load.c"
                    "json/strbuffer.c"
                    "json/strconv.c"
                    "json/utf.c"
                    "json/error.c"
                    "json/dump.c"
                    "json/hashtable_seed.c")

set(COMPONENT_ADD_INCLUDEDIRS ""
                              "json")

register_component()