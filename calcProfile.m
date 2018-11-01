datafile_left = 'srtm_44_03.tif';
datafile_right = 'srtm_45_03.tif';

ll0 = [47 + 17 / 60 + 49.40 / 3600, 39 + 56 / 60 + 42.31 / 3600];

p1  = [47 + 12 / 60 + 22.10 / 3600, 40 + 04 / 60 + 58.60 / 3600];
p2  = [47 + 11 / 60 + 18.20 / 3600, 40 + 06 / 60 + 59.90 / 3600];
p3  = [47 + 11 / 60 + 17.20 / 3600, 40 + 08 / 60 + 59.40 / 3600];
p4  = [47 + 10 / 60 + 37.70 / 3600, 40 + 10 / 60 + 39.60 / 3600];
p5  = [47 + 09 / 60 + 45.80 / 3600, 40 + 10 / 60 + 38.60 / 3600];
p6  = [47 + 09 / 60 + 17.80 / 3600, 40 + 12 / 60 + 10.20 / 3600];

end_point = p4;


[dem_left, R_left] = geotiffread(datafile_left);
dem_left = double(dem_left);

[dem_right, R_right] = geotiffread(datafile_right);
dem_right = double(dem_right);

t = 0:0.0005:1;
alt = zeros(size(t));
dist = zeros(size(t));
[dem, R] = geotiffread(datafile_left);
for i = 1:length(t)
    t_ = t(i);
    display(sprintf('%d of %d\n',i, length(t)));
    pos = ll0 * (1 - t_) + end_point * t_;
    if pos(2) < R_left.LongitudeLimits(2) && pos(2) > R_left.LongitudeLimits(1)
        alt(i) = get_altitude(pos, dem_left, R_left);
    elseif pos(2) < R_right.LongitudeLimits(2) && pos(2) > R_right.LongitudeLimits(1)
        alt(i) = get_altitude(pos, dem_right, R_right);
    else
        error ('Point is out of known files');
    end
    
    dist(i) = norm(lla2flat([pos, 0], ll0, 0, 0));
end
plot(dist, alt);
profile = [dist', alt'];
csvwrite('profile.dat', profile);
