rm -rf $1
g++ -lGL -lglut $1.cpp -o $1
./$1
