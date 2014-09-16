rm -f parsort.so
rm -rf build
python setup.py build
cp build/lib.*/parsort.so ./
rm -rf build
