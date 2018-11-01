function alt = getAltitude(pos_latlon, dem, R)
lat_lim = R.LatitudeLimits;
lon_lim = R.LongitudeLimits;

assert(lat_lim(1) < pos_latlon(1), 'Lattitude is out of limits');
assert(lat_lim(2) > pos_latlon(1), 'Lattitude is out of limits');

assert(lon_lim(1) < pos_latlon(2), 'Longitude is out of limits');
assert(lon_lim(2) > pos_latlon(2), 'Longitude is out of limits');

if strcmp(R.ColumnsStartFrom, 'north')
    % Expect float value and further interpolation
    column_index = (lat_lim(2) - pos_latlon(1)) / R.CellExtentInLatitude + 1;
else
    error('Unknowt type of GEO TIFF file');
end

if strcmp(R.RowsStartFrom, 'west')
    row_index = ( - lon_lim(1) + pos_latlon(2)) / R.CellExtentInLatitude + 1;
else
    error('Unknowt type of GEO TIFF file');
end
% Interpolate data:
alt = interp2(dem, row_index, column_index, 'linear');

end
