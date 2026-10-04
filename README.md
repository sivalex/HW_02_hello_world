# Параметризованный модуль Hello World

## Установка дополнительных пакетов

```bash
sudo apt install clang-format
```

## ASCII-коды символов строки "Hello, world!":

```text
48 65 6c 6c 6f 2c 20 77 6f 72 6c 64 21
```

## Запуск Kbuild

```bash
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
```
