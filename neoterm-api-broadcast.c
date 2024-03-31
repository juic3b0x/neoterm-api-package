/* neoterm-api.c - helper binary for calling neoterm api classes
 * Usage: neoterm-api ${API_METHOD} ${ADDITIONAL_FLAGS}
 * This executes
 *   am broadcast io.neoterm.api/.NeoTermApiReceiver \
 *   --es socket_input ${INPUT_SOCKET} \
 *   --es socket_output ${OUTPUT_SOCKET} \
 *   --es api_method ${API_METHOD} \
 *   ${ADDITIONAL_FLAGS}
 * where ${INPUT_SOCKET} and ${OUTPUT_SOCKET} are addresses to linux
 * abstract namespace sockets, used to pass on stdin to the java
 * implementation and pass back output from java to stdout.
 */

#include "neoterm-api.h"

int main(int argc, char** argv) {
    /* Run the api command */
    int fd = run_api_command(argc, argv);

    if (fd != -1) { exec_callback(fd); }

    return 0;
}
