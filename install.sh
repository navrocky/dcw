#!/bin/bash

set -e

curl -fL https://github.com/navrocky/dcw/releases/download/1.3.0/dcw -o /usr/local/bin/dcw
chmod +x /usr/local/bin/dcw
curl -fL https://github.com/navrocky/dcw/raw/master/completion.bash -o /etc/bash_completion.d/dcw_completion.bash

echo "== Installation completed successfully =="
