rm rt_test ft_test
cp ../objs/main.o ../

echo "Test 1: one file/cmd (no options)"

echo ".././ft_nm ../ft_nm >> ft_test"
.././ft_nm ../ft_nm >> ft_test
echo "nm ../ft_nm >> rt_test"
nm ../ft_nm >> rt_test

echo ".././ft_nm ../main.o >> ft_test"
.././ft_nm ../main.o >> ft_test
echo "nm ../main.o >> rt_test"
nm ../main.o >> rt_test

echo ".././ft_nm /lib32/libpthread.so.0 >> ft_test"
.././ft_nm /lib32/libpthread.so.0 >> ft_test
echo "nm /lib32/libpthread.so.0 >> rt_test"
nm /lib32/libpthread.so.0 >> rt_test



echo "\nTest 2: one file/cmd (option -g)"

echo ".././ft_nm ../ft_nm -g >> ft_test"
.././ft_nm ../ft_nm -g >> ft_test
echo "nm ../ft_nm -g >> rt_test"
nm ../ft_nm -g >> rt_test

echo ".././ft_nm ../main.o -g >> ft_test"
.././ft_nm ../main.o -g >> ft_test
echo "nm ../main.o -g >> rt_test"
nm ../main.o -g >> rt_test

echo ".././ft_nm /lib32/libpthread.so.0 -g >> ft_test"
.././ft_nm /lib32/libpthread.so.0 -g >> ft_test
echo "nm /lib32/libpthread.so.0 -g >> rt_test"
nm /lib32/libpthread.so.0 -g >> rt_test


echo "\nTest 3: one file/cmd (-u)"

echo ".././ft_nm ../ft_nm -u >> ft_test"
.././ft_nm ../ft_nm -u >> ft_test
echo "nm ../ft_nm -u >> rt_test"
nm ../ft_nm -u >> rt_test

echo ".././ft_nm ../main.o -u >> ft_test"
.././ft_nm ../main.o -u >> ft_test
echo "nm ../main.o -u >> rt_test"
nm ../main.o -u >> rt_test

echo ".././ft_nm /lib32/libpthread.so.0 -u >> ft_test"
.././ft_nm /lib32/libpthread.so.0 -u >> ft_test
echo "nm /lib32/libpthread.so.0 -u >> rt_test"
nm /lib32/libpthread.so.0 -u >> rt_test


echo "\nTest 4: one file/cmd (-p)"

echo ".././ft_nm ../ft_nm -p >> ft_test"
.././ft_nm ../ft_nm -p >> ft_test
echo "nm ../ft_nm -p >> rt_test"
nm ../ft_nm -p >> rt_test

echo ".././ft_nm ../main.o -p >> ft_test"
.././ft_nm ../main.o -p >> ft_test
echo "nm ../main.o -p >> rt_test"
nm ../main.o -p >> rt_test

echo ".././ft_nm /lib32/libpthread.so.0 -p >> ft_test"
.././ft_nm /lib32/libpthread.so.0 -p >> ft_test
echo "nm /lib32/libpthread.so.0 -p >> rt_test"
nm /lib32/libpthread.so.0 -p >> rt_test


echo "\nTest 5: one file/cmd (-r)"

echo ".././ft_nm ../ft_nm -r >> ft_test"
.././ft_nm ../ft_nm -r >> ft_test
echo "nm ../ft_nm -r >> rt_test"
nm ../ft_nm -r >> rt_test

echo ".././ft_nm ../main.o -r >> ft_test"
.././ft_nm ../main.o -r >> ft_test
echo "nm ../main.o -r >> rt_test"
nm ../main.o -r >> rt_test

echo ".././ft_nm /lib32/libpthread.so.0 -r >> ft_test"
.././ft_nm /lib32/libpthread.so.0 -r >> ft_test
echo "nm /lib32/libpthread.so.0 -r >> rt_test"
nm /lib32/libpthread.so.0 -r >> rt_test

echo "\nTest 6: multiple files/cmd (multiple options)"

echo ".././ft_nm ../ft_nm /lib32/libpthread.so.0 ../main.o -rg >> ft_test"
.././ft_nm ../ft_nm /lib32/libpthread.so.0 ../main.o -rg >> ft_test
echo "nm ../ft_nm /lib32/libpthread.so.0 ../main.o -rg >> rt_test"
nm ../ft_nm /lib32/libpthread.so.0 ../main.o -rg >> rt_test

echo ".././ft_nm ../ft_nm /lib32/libpthread.so.0 ../main.o -pru >> ft_test"
.././ft_nm ../ft_nm /lib32/libpthread.so.0 ../main.o -pru >> ft_test
echo "nm ../ft_nm /lib32/libpthread.so.0 ../main.o -pru >> rt_test"
nm ../ft_nm /lib32/libpthread.so.0 ../main.o -pru >> rt_test

echo ".././ft_nm ../ft_nm /lib*/* ../main.o -gpru >> ft_test"
.././ft_nm ../ft_nm /lib*/* ../main.o -gpru >> ft_test
echo "nm ../ft_nm /lib*/* ../main.o -gpru >> rt_test"
nm ../ft_nm /lib*/* ../main.o -gpru >> rt_test

echo ".././ft_nm /lib*/* /usr/bin/* >> ft_test"
.././ft_nm /lib*/* /usr/bin/* >> ft_test
echo ".././nm /lib*/* /usr/bin/* >> rt_test"
nm /lib*/* /usr/bin/* >> rt_test
