#!/usr/bin/env bash
# build.sh — configure, build, and debug your project with colored output

# ANSI color codes
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
R="\033[0m"  # Reset

# Settings
PROJECT_NAME="app"
BUILD_DIR="build"
BINARY="./${BUILD_DIR}/${PROJECT_NAME}/${PROJECT_NAME}"

# Detect number of parallel jobs
if [[ "$OSTYPE" == "darwin"* ]]; then
    JOBS=$(sysctl -n hw.ncpu)
else
    JOBS=$(nproc)
fi

# Ensure Ninja is available
if ! command -v ninja &> /dev/null; then
    echo -e "${RED}Error:${R} Ninja not found. Please install Ninja (e.g. 'brew install ninja')."
    exit 1
fi

# CMake flags (all via -D, no persistent CMAKE_CXX_FLAGS)
CMAKE_FLAGS=(
  -G Ninja
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5
  -DCMAKE_CXX_FLAGS=""                # clear any old flags
  -DFILAMENT_WARNINGS=OFF
  -DFILAMENT_FATAL_WARNINGS=OFF
  -DSPIRV_WERROR=OFF
  -DCMAKE_OSX_DEPLOYMENT_TARGET=12.6
)

configure() {
    echo -e "${YELLOW}>> Cleaning and configuring in '${BUILD_DIR}'...${R}"
    rm -rf "${BUILD_DIR}"
    mkdir -p "${BUILD_DIR}"

    cmake -B "${BUILD_DIR}" -S . "${CMAKE_FLAGS[@]}"
    if [[ $? -ne 0 ]]; then
        echo -e "${RED}Error running CMake.${R}"
        exit 1
    fi
    echo -e "${GREEN}CMake configuration succeeded.${R}"
}

build() {
    echo -e "${YELLOW}>> Building with Ninja (${JOBS} jobs)...${R}"
    ninja -C "${BUILD_DIR}" -j "${JOBS}"
    if [[ $? -eq 0 ]]; then
        echo -e "${GREEN}Build succeeded.${R}"
    else
        echo -e "${RED}Build failed.${R}"
        exit 1
    fi
}

build_verbose() {
    echo -e "${YELLOW}>> Building with Ninja (verbose, ${JOBS} jobs)...${R}"
    ninja -C "${BUILD_DIR}" -v -j "${JOBS}"
}

trace_config() {
    echo -e "${BLUE}>> Running CMake with --trace-expand (output to cmake-trace.log)...${R}"
    rm -rf "${BUILD_DIR}"
    mkdir -p "${BUILD_DIR}"
    cmake -B "${BUILD_DIR}" -S . --trace-expand | tee cmake-trace.log
    echo -e "${GREEN}Trace log saved to cmake-trace.log${R}"
}

grep_off() {
    echo -e "${YELLOW}>> Searching for literal 'OFF' in build directory...${R}"
    grep -R "OFF" "${BUILD_DIR}" -n || echo -e "${GREEN}No occurrences of 'OFF' found.${R}"
}

run_app() {
    if [[ ! -x "${BINARY}" ]]; then
        echo -e "${RED}Binary not found: ${BINARY}${R}"
        exit 1
    fi
    echo -e "${YELLOW}>> Running '${PROJECT_NAME}'...${R}"
    "${BINARY}"
}

clean() {
    echo -e "${YELLOW}>> Cleaning '${BUILD_DIR}'...${R}"
    rm -rf "${BUILD_DIR}"
    echo -e "${GREEN}Build directory removed.${R}"
}

help() {
    echo -e "${BLUE}Usage:${R} $0 <command>"
    echo
    echo -e "  ${YELLOW}configure${R}      Clean and run CMake"
    echo -e "  ${YELLOW}build${R}          Build with Ninja"
    echo -e "  ${YELLOW}build-verbose${R}  Build with Ninja in verbose mode"
    echo -e "  ${YELLOW}trace-config${R}   Configure with CMake --trace-expand"
    echo -e "  ${YELLOW}grep-off${R}       Search for literal 'OFF' in build directory"
    echo -e "  ${YELLOW}clean${R}          Remove the build directory"
    echo -e "  ${YELLOW}run${R}            Build (if needed) and run the application"
    echo -e "  ${YELLOW}help${R}           Show this help message"
}

case "$1" in
    configure)      configure ;;
    build)          configure && build ;;
    build-verbose)  configure && build_verbose ;;
    trace-config)   trace_config ;;
    grep-off)       grep_off ;;
    clean)          clean ;;
    run)            configure && build && run_app ;;
    *)              help ;;
esac
