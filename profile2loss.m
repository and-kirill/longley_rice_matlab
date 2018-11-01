function [] = profile2loss(hTxm, hRxm, frqMhz, prfFile, outFile)
% - hTxm:    TX antennta height [m]
% - hRxm:    RX antenna height [m]
% - frqMhz:  Carrier frequency [MHz]
% - prfFile: profile containing terrain profile in [x, alt] CSV format in
%            meters
% - outFile: output file to store loss values

% Signal polarization. Default antennas assume vertical polarization
signal_params.polarization = 'vertical';
% Carrier frequency [MHz]
signal_params.frequencyMhz = frqMhz;
% Earth surface dielectric constant, see http://www.qsl.net/n9zia/conduct.html for details
env_params.epsDielectEarth = 15.0000;
% Earth surface conductivity constant, see http://www.qsl.net/n9zia/conduct.html for details
env_params.conductivityEarth = 0.0050;
% Earth-to-air refractivity coefficient https://www.fig.net/pub/fig_2002/Js28/JS28_rueger.pdf
env_params.refractivityEarth = 310.0000;
% Climate type. Possible string values are:
%   - 'Equatorial',
%   - 'Continental Subtropical',
%   - 'Maritime Tropical',
%   - 'Desert',
%   - 'Continental Temperate',
%   - 'Maritime Temperate, Over Land',
%   - 'Maritime Temperate, Over Sea'.
env_params.radioClimate = 'Continental Temperate';

env_params.locpct = 0.9;
env_params.timepct = 0.9;
env_params.confpct = 0.9;


data = csvread(prfFile);

alt  = data(:, 2)';
dist = data(:, 1)';

terrain_params.profileStep = dist(2) - data(1);
N = length(dist);
loss = zeros(size(dist));
for i = 1:N
    terrain_params.profile = alt(1:i);
    [lossdb, proptype] = itmlrProfile(hTxm, hRxm, signal_params, terrain_params, env_params);
    loss(i) = lossdb;
end

% Create output:
result.signal_params = signal_params;
result.env_params =env_params;
result.terrain_params = terrain_params;

result.hTxm = hTxm;
result.hRxm = hRxm;

result.loss = loss;

save('-mat7-binary', outFile, 'result');
