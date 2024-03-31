cmake_minimum_required(VERSION 3.0.0)
project(neoterm-api)
include(GNUInstallDirs)

set(NEOTERM_PREFIX ${CMAKE_INSTALL_PREFIX})

add_library(neoterm-api SHARED neoterm-api.c)
add_library(neoterm-api-static STATIC neoterm-api.c)
set_target_properties(neoterm-api-static PROPERTIES OUTPUT_NAME neoterm-api)

add_executable(neoterm-api-broadcast neoterm-api-broadcast.c)
target_link_libraries(neoterm-api-broadcast neoterm-api-static)

# TODO: get list through regex or similar
set(script_files
  scripts/neoterm-api-start
  scripts/neoterm-api-stop
  scripts/neoterm-audio-info
  scripts/neoterm-battery-status
  scripts/neoterm-brightness
  scripts/neoterm-call-log
  scripts/neoterm-camera-info
  scripts/neoterm-camera-photo
  scripts/neoterm-clipboard-get
  scripts/neoterm-clipboard-set
  scripts/neoterm-contact-list
  scripts/neoterm-dialog
  scripts/neoterm-download
  scripts/neoterm-fingerprint
  scripts/neoterm-infrared-frequencies
  scripts/neoterm-infrared-transmit
  scripts/neoterm-job-scheduler
  scripts/neoterm-keystore
  scripts/neoterm-location
  scripts/neoterm-media-player
  scripts/neoterm-media-scan
  scripts/neoterm-microphone-record
  scripts/neoterm-nfc
  scripts/neoterm-notification
  scripts/neoterm-notification-channel
  scripts/neoterm-notification-list
  scripts/neoterm-notification-remove
  scripts/neoterm-saf-create
  scripts/neoterm-saf-dirs
  scripts/neoterm-saf-ls
  scripts/neoterm-saf-managedir
  scripts/neoterm-saf-mkdir
  scripts/neoterm-saf-read
  scripts/neoterm-saf-rm
  scripts/neoterm-saf-stat
  scripts/neoterm-saf-write
  scripts/neoterm-sensor
  scripts/neoterm-share
  scripts/neoterm-sms-inbox
  scripts/neoterm-sms-list
  scripts/neoterm-sms-send
  scripts/neoterm-speech-to-text
  scripts/neoterm-storage-get
  scripts/neoterm-telephony-call
  scripts/neoterm-telephony-cellinfo
  scripts/neoterm-telephony-deviceinfo
  scripts/neoterm-toast
  scripts/neoterm-torch
  scripts/neoterm-tts-engines
  scripts/neoterm-tts-speak
  scripts/neoterm-usb
  scripts/neoterm-vibrate
  scripts/neoterm-volume
  scripts/neoterm-wallpaper
  scripts/neoterm-wifi-connectioninfo
  scripts/neoterm-wifi-enable
  scripts/neoterm-wifi-scaninfo
)

make_directory(scripts)
foreach(file ${script_files})
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${file}.in
    ${file} @ONLY
  )
endforeach()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/neoterm-callback.in
  neoterm-callback @ONLY
)

install(
  FILES ${CMAKE_BINARY_DIR}/neoterm-api-broadcast
  DESTINATION ${CMAKE_INSTALL_PREFIX}/libexec
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

# Create a symlink for neoterm-api-broadcast->neoterm-api for backwards
# compatibility
INSTALL(CODE "execute_process( \
  COMMAND ${CMAKE_COMMAND} -E create_symlink \
  neoterm-api-broadcast \
  ${CMAKE_INSTALL_PREFIX}/libexec/neoterm-api \
  )"
)

install(
  FILES
    ${CMAKE_BINARY_DIR}/libneoterm-api.so
    ${CMAKE_BINARY_DIR}/libneoterm-api.a
  TYPE LIB
)

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/neoterm-api.h
  TYPE INCLUDE
)

foreach(file ${script_files})
  install(
    FILES ${CMAKE_BINARY_DIR}/${file}
    TYPE BIN
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  )
endforeach()

install(
  FILES ${CMAKE_BINARY_DIR}/neoterm-callback
  DESTINATION ${CMAKE_INSTALL_PREFIX}/libexec
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)
