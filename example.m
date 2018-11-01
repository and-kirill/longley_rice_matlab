clear;
startup;
%% Demonstration example for ITMLR profile generation routines
latlon_start  = [56.350471, 37.410416]; % [lat lon] format in degrees
latlon_finish = [56.450087, 37.333431]; % [lat lon] format in degrees
% DEM is downloaded from http://www.cgiar-csi.org/data/srtm-90m-digital-elevation-database-v4-1
demfile = 'srtm/srtm_44_01.tif';
% Profile 
prffile = 'dmitrov.csv';
lossfile = 'dmitrov.mat';

dem2profile(latlon_start, latlon_finish, demfile, prffile);

h_tx = 6;   % Transmitter antenna height [m]. TX is located at start point
h_rx = 1.5; % Receiver antenna height [m]. RX is located at start point
frq_mhz = 2600; % Carrier frequency

profile2loss(h_tx, h_rx, frq_mhz, prffile, lossfile);

plotLoss(lossfile);
