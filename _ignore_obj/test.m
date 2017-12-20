lambdax = 1;
myStruct = PoisssonPointProcess_cpp_mex(lambdax)

figure
bar([myStruct.eventsNumOfEvents], [myStruct.eventsFrequency], 'FaceColor', [0 .5 .5], 'EdgeColor', [0 .9 .9], 'LineWidth', 1.5)
xlabel('Number of Events')
ylabel('Frequency')
title('Number of Poisson Events Over Fixed Time')
grid on