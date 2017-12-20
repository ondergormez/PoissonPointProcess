lambdax = 1;
myStruct = PoisssonPointProcess_cpp_mex(lambdax)

figure
plot([myStruct.timelineTime], [myStruct.timelineNumOfEvents], 'LineWidth', 1.5)
xlabel('Time')
ylabel('Number of Events')
title('Observation of Fixed Number of Poisson Events')
grid on

figure
bar([myStruct.timesWaitingTime], [myStruct.timesFrequency], 'FaceColor', [0 .5 .5], 'EdgeColor', [0 .9 .9], 'LineWidth', 1.5)
xlabel('Waiting Time')
ylabel('Frequency')
title('Waiting Times Observed Over Fixed Time')
grid on

figure
bar([myStruct.eventsNumOfEvents], [myStruct.eventsFrequency], 'FaceColor', [0 .5 .5], 'EdgeColor', [0 .9 .9], 'LineWidth', 1.5)
xlabel('Number of Events')
ylabel('Frequency')
title('Number of Poisson Events Over Fixed Time')
grid on