% Title: Ball & Beam PID simulation script
% Author: Omar Badreldin
% Date: August 15th, 2026
% Description: This script initializes the parameters for the Ball & Beam
%              model, executes a Simulink simulation, and processes the 
%              results to generate relevant plots and analytics.
% Usage: Run this script before running the ballBeamSimulink.slx model.


% Initialise parameters
m = 0.0027; % kg
r = 0.02; % m 
d = 0.053; % m
g = -9.81; % m/s^2
l = 0.36; % m
j = 0.000000432; % kg.m^2
% Initialise coefficients of G_1 transfer function block
Num = -m*g*d/l/(j/r^2+m);
Den = [1 0 0]; 
% PID gains
Kp = 1;
Ki = 0.000001;
Kd = 9.5;
% Define the transfer function for the system
sys_tf = tf(Num, Den);
% Define the PID controller transfer function
C = tf([Kd, Kp, Ki], [1, 0]);
% Create the open-loop system
sys_open = sys_tf * C;
% Create the closed-loop system
sys_cl = minreal((sys_tf)*(C))/(1+(sys_tf)*(C))
% Run the simulink model from workspace
open_system('ballBeamSimulink');
res = sim("ballBeamSimulink");
ball_pos = res.sys_out.data;
time = res. sys_out.time;
% Plot the ball position over time
figure (1);
plot(time, ball_pos);
xlabel('Time (s)');
ylabel('Ball Position (m)');
title('Ball Position Response');
grid minor;
% Display step response characteristics
info = stepinfo(ball_pos, time, 0.18);
disp(info);
% Analyze the frequency response of the closed-loop system using bode plot
figure(2);
bode(sys_cl);
title('Bode Plot of Closed-Loop System');
grid minor;

