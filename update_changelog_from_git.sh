#!/bin/bash

set -e

CHANGELOG="CHANGELOG.md"

getLastTagFromChangeLog() {
  grep -oE "([0-9X]+\.){2}[0-9X]" <"$1" | head -n1
}

printNewRelease() {
  LAST_VERSION="$1"

  echo "# X.X.X ($(date +%Y-%m-%d))"
  echo

  if [ -z "${LAST_VERSION}" ]; then
    COMMITS="HEAD"
  else
    COMMITS="${LAST_VERSION}..HEAD"
  fi
  GIT_LOG_COMMAND="git log --format=%s ${COMMITS}"
  $GIT_LOG_COMMAND | while IFS=$'\n' read -r LINE; do
    echo "- $LINE"
  done

  echo
}

generateChangeLog() {
  printNewRelease >>${CHANGELOG}

  echo "The initial ${CHANGELOG} generated"
}

updateChangeLog() {
  LAST_VERSION="$1"

  if [ "${LAST_VERSION}" == "X.X.X" ]; then
    echo "The ${CHANGELOG} already contains raw git log"
    exit 1
  fi

  TMP_CHANGELOG="${CHANGELOG}.tmp"
  [ -f "${TMP_CHANGELOG}" ] && rm ${TMP_CHANGELOG}

  # copy original change log and insert new release
  cat ${CHANGELOG} | while IFS=$'\n' read -r LINE; do
    if [[ "${LINE}" == *"${LAST_VERSION}"* ]]; then
      printNewRelease "${LAST_VERSION}" >>${TMP_CHANGELOG}
    fi
    echo "${LINE}" >>${TMP_CHANGELOG}
  done

  mv ${TMP_CHANGELOG} ${CHANGELOG}

  echo "The ${CHANGELOG} updated with a recent commits after the tag ${LAST_VERSION}"
}

if [ -f "${CHANGELOG}" ]; then
  LAST_VERSION=$(getLastTagFromChangeLog ${CHANGELOG})
fi

if [ -z "${LAST_VERSION}" ]; then
  generateChangeLog
else
  updateChangeLog "${LAST_VERSION}"
fi
