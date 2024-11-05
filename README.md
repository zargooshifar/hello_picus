compile command:
```
mkdir build; cd build
cmake ..
make
```

binary files will be at build/src folder:
```
cd build
./src/gpio_example
./src/cuda_example ../kitty.jpeg
```



**picus is running on 25W mode as default. you can change this in GUI or by run bellow command:**
```
# for check power mode
nvpmodel -q
# change to max power mode (25W)
nvpmodel -m 0
```

power modes:

| Power Mode | Description |
|------------|-------------|
| 0          | MAX         |
| 1          | 10W         |
| 2          | 15W         |
| 3          | 25W         |
