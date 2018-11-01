function [] = dem2profile(latlon_start, latlon_finish, demfile, prffile, N)
% Calulate profile connecting lstlon_start and latlon_end points.
% Each point is a decimal values [lat lon] in degrees
% demfile provides the source of sigital elevation map
% prffile provides the output CSV file written in the form
%   len_1,alt_1
%   ..........
%   len_N,alt_N
% with N -- profile length.

[dem, R] = geotiffread(demfile);
dem = double(dem);

% Plot straight line in local euclidean reference frame
euclidean_end = lla2flat([latlon_finish, 0], latlon_start, 0, 0);
display(sprintf('Communication line length: %2.2f m.', norm(euclidean_end)));

if nargin == 4
    N = 600; % The number of points in the profile
end

step_vector = euclidean_end / N;

% Calculate profile: a set of altitudes at equidistant points along start-end line
alt = zeros(1, N + 1);
dist = (0:N) * norm(step_vector);
alt(1) = getAltitude(latlon_start, dem, R);

for i = 1:N
    pos_latlon = flat2lla(step_vector * i, latlon_start, 0, 0);
    alt(i + 1) = getAltitude(pos_latlon, dem, R);
end
%% Visualize and save data
plot(dist, alt);
profile = [dist', alt'];
csvwrite(prffile, profile);