install requirements:
opencv + cuda support (before start installing opencv change powermode to MAX)
```

chmod +x install_opencv_with_cuda_support.sh
./install_opencv_with_cuda_support.sh
```

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



**picus is running on 15W mode as default. you can change this in GUI or by run following command:**
```
# for check power mode
sudo nvpmodel -q
# change to max power mode (25W)
sudo nvpmodel -m 0
```

power modes:

| Power Mode | Description |
|------------|-------------|
| 0          | MAX         |
| 1          | 10W         |
| 2          | 15W         |
| 3          | 25W         |
