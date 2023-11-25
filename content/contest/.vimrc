set nocp is ic hls sm
set rnu nu ai si
set sw=4 ts=4 et

" :Hash on selection to get hash for verification
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
