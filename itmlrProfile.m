function [lossdb, proptype, deltaH, errnum]= itmlrProfile(txant_height, rxant_height, signal_params, terrain_params, env_params)

% Check that antenna heights are a positive double
if ~isfloat(txant_height) || txant_height <= 0
    error('ITMLR:point:checkInputs', 'Transmission antenna height must be positive double');
end
if ~isfloat(txant_height) || txant_height <= 0
    error('ITMLR:point:checkInputs', 'Transmission antenna height must be positive double');
end

% Signal parameters structure must contain polarization field (string) and carrier frequency (MHz)
if ~isfield(signal_params, 'polarization')
    error('ITMLR:point:checkInputs', 'Signal parameters structure must contain \"polarization\" field');
end

if strcmp(signal_params.polarization, 'vertical')
    polarization = 1;
elseif strcmp(signal_params.polarization, 'horizontal')
    polarization = 0;
else
    error('ITMLR:point:checkInputs', 'Signal parameters polarization must be whether \"vertical\" or \"horizontal\"');
end

% Check that frequency is positive float value
if ~isfield(signal_params, 'frequencyMhz')
    error('ITMLR:point:checkInputs', 'Signal parameters structure must contain \"frequencyMhz\" field');
end

if ~isfloat(signal_params.frequencyMhz) || signal_params.frequencyMhz <= 0
    error('ITMLR:point:checkInputs', 'Signal carrier frequency must be a positive double value');
end

% Check terrain parameters:

if ~isfield(terrain_params, 'profile')
    error('ITMLR:point:checkInputs', 'Terrain parameters structure must contain \"profile\" field');
end

if sum(isnan(terrain_params.profile)) > 0
    error('ITMLR:point:checkInputs', 'Terrain profile should not contain any \"NaN\"');
end

if ~isfield(terrain_params, 'profileStep')
    error('ITMLR:point:checkInputs', 'Terrain parameters structure must contain \"profileStep\" field');
end

% Check environment with filling defaults:

if ~isfield(env_params, 'epsDielectEarth')
    % See http://www.qsl.net/n9zia/conduct.html for details
    epsDielectEarth_default = 15;
    warning('ITMLR:point:checkInputs', 'Environment parameters structure does not contain \"epsDielectEarth\" field. Set default to %2.4f', epsDielectEarth_default);
    env_params.epsDielectEarth = epsDielectEarth_default;
end

if ~isfield(env_params, 'conductivityEarth')
    % See http://www.qsl.net/n9zia/conduct.html for details
    conductivityEarth_default = 0.005;
    warning('ITMLR:point:checkInputs', ...
        'Environment parameters structure does not contain \"conductivityEarth\" field. Set default to %2.4f', ...
        conductivityEarth_default);
    env_params.conductivityEarth = conductivityEarth_default;
end

if ~isfield(env_params, 'refractivityEarth')
    % See http://www.softwright.com/faq/engineering/prop_longley_rice.html for details
    refractivityEarth_default = 301; % Recommended value by Longley and Rice
    warning('ITMLR:point:checkInputs', ...
        'Environment parameters structure does not contain \"refractivityEarth\" field. Set default to %2.4f', ...
        refractivityEarth_default);
    env_params.refractivityEarth = refractivityEarth_default;
end

if ~isfield(env_params, 'radioClimate')
    % radioClimate: 1-Equatorial, 2-Continental Subtropical, 3-Maritime Tropical,
    %                4-Desert, 5-Continental Temperate, 6-Maritime Temperate, Over Land,
    %                7-Maritime Temperate, Over Sea
    warning('ITMLR:point:checkInputs', ...
        'Environment parameters structure does not contain \"radioClimate\" field. Set default to \"Continental Temperate\"');
    radioClimate = 5;
elseif strcmp(env_params.radioClimate, 'Equatorial')
    radioClimate = 1;
elseif strcmp(env_params.radioClimate, 'Continental Subtropical')
    radioClimate = 2;
elseif strcmp(env_params.radioClimate, 'Maritime Tropical')
    radioClimate = 3;
elseif strcmp(env_params.radioClimate, 'Desert')
    radioClimate = 4;
elseif strcmp(env_params.radioClimate, 'Continental Temperate')
    radioClimate = 5;
elseif strcmp(env_params.radioClimate, 'Maritime Temperate, Over Land')
    radioClimate = 6;
elseif strcmp(env_params.radioClimate, 'Maritime Temperate, Over Sea')
    radioClimate = 7;
else
    error('ITMLR:point:checkInputs', 'Environment parameters must contain \"radioClimate\" field set as a proper string');
end

% Read confidence levels:
if ~isfield(env_params, 'locpct')
    locpct_default = 0.9;
    warning('ITMLR:point:checkInputs', 'Environment parameters structure does not contain \"locpct\" field. Set default to %2.4f', locpct_default);
    env_params.locpct = locpct_default;
end

if env_params.locpct < 0.01 || env_params.locpct > 0.99
    error('ITMLR:point:checkInputs', 'Parameter \"lopct\" must be within [0.01; 0.99] interval');
end

if ~isfield(env_params, 'timepct')
    timepct_default = 0.9;
    warning('ITMLR:point:checkInputs', 'Environment parameters structure does not contain \"timepct\" field. Set default to %2.4f', timepct_default);
    env_params.timepct = timepct_default;
end

if env_params.timepct < 0.01 || env_params.timepct > 0.99
    error('ITMLR:point:checkInputs', 'Parameter \"timepct\" must be within [0.01; 0.99] interval');
end

if ~isfield(env_params, 'confpct')
    confpct_default = 0.9;
    warning('ITMLR:point:checkInputs', 'Environment parameters structure does not contain \"confpct\" field. Set default to %2.4f', confpct_default);
    env_params.confpct = confpct_default;
end

if env_params.confpct < 0.01 || env_params.confpct > 0.99
    error('ITMLR:point:checkInputs', 'Parameter \"confpct\" must be within [0.01; 0.99] interval');
end



% Call ITMLR C++ implementation:
[lossdb, proptype, deltaH, errnum] = itmlrPoint(...
    terrain_params.profile, ...
    terrain_params.profileStep, ...
    txant_height, rxant_height, ...
    env_params.epsDielectEarth, ...
    env_params.conductivityEarth, ...
    env_params.refractivityEarth, ...
    signal_params.frequencyMhz, ...
    radioClimate, ...
    polarization, ...
    env_params.timepct, ...
    env_params.locpct, ...
    env_params.confpct ...
);
end
