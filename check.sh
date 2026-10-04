#!/usr/bin/env sh

module_name="hello_world"

set_idx()
{
    sudo sh -c "echo $1 > /sys/module/$module_name/parameters/idx"
}

set_ch_val()
{
    sudo sh -c "echo $1 > /sys/module/$module_name/parameters/ch_val"
}

echo "Check script started..."

chars="48 65 6c 6c 6f 2c 20 77 6f 72 6c 64 21"

index=0
for ch_val in $chars; do
    set_idx $index
    set_ch_val "$ch_val"
    index=$((index+1))
done

echo "Check script finished..."
