lambdax = 1;
myStruct = PoisssonPointProcess_cpp_mex(lambdax)

figure
plot(myStruct.number, myStruct.value)
bar([myStruct.number], [myStruct.value])