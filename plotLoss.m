function [] = plotLoss(ifile)

%% System parameters for Uplink link budget
ul_tx_power = 23;           % dbm
ul_rx_sensitivity = -100.8; % dBm for ranberry cell-1000
ul_rx_cable_loss = 0.0;     % dB
ul_rx_gain = 15.0;          % dB
ul_tx_gain = 0.0;           % db

%% System parameters for Downlink link budget
dl_tx_power = 30;            % dbm for ranverry cell-1000
dl_rx_sensitivity = -98.0;   % dBm for UE
dl_rx_cable_loss = 0.0;      % dB
dl_tx_gain = 15.0;           % dB
dl_rx_gain = 0.00;           % dB

%% Load data
loss_data = load(ifile);

%% Visualize propagation
N = length(loss_data.result.terrain_params.profile);
dist = (1:N) * loss_data.result.terrain_params.profileStep;

figure;
plotyy(dist, -loss_data.result.loss, dist, loss_data.result.terrain_params.profile);
hold on;
plot(dist, -loss_data.result.loss, 'b--');
grid on;
legend('DL', 'UL');

%% Calculate link budget
maxloss_ul = ul_tx_power - ul_rx_sensitivity - ul_rx_cable_loss + ul_rx_gain + ul_tx_gain;
maxloss_dl = dl_tx_power - dl_rx_sensitivity - dl_rx_cable_loss + dl_rx_gain + dl_tx_gain;

display(sprintf('Maximum allowed loss in DL: %2.4f', maxloss_dl));
display(sprintf('Maximum allowed loss in UL: %2.4f', maxloss_ul));

display(sprintf('DL link budget: %2.2f dB', maxloss_dl - loss_data.result.loss(end)));
display(sprintf('UL link budget: %2.2f dB', maxloss_ul     - loss_data.result.loss(end)));

%% Visualize link budget
figure; % For band 7
plot(dist, maxloss_dl - loss_data.result.loss, 'r', 'LineWidth', 2);
hold on;
plot(dist, maxloss_ul - loss_data.result.loss, 'b', 'LineWidth', 2);
legend('DL 2625 MHz', 'Band 7 UL 2505 MHz');
grid on;
plot(dist, zeros(size(dist)), 'k', 'LineWidth', 2);
