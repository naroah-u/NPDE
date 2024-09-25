for i = 0:3
    tiledlayout(1, 2, 'TileSpacing', 'tight');
    file_name = "output_" + i + ".txt";
    table = readmatrix(file_name);
    x = table(:, 1);
    y = table(:, 2:end);
    error = abs([y(:, 2) - y(:, 1) y(:, 3) - y(:, 1)]);
    nexttile
    plot(x, y); title("m=" + size(x,1));legend('v', 'v_{10}', 'v_{100}');
    nexttile
    plot(x, error); title("m=" + size(x,1) + "的误差图像");legend('v_{10}', 'v_{100}');
    picture_name = ".png";
    if i >= 2 
        picture_name = "修正" + picture_name;
    end
    position = get(gcf, 'Position');
    set(gcf, 'unit', 'centimeters', 'Position', [20 5 20 10]);
    saveas(gcf, "m=" + size(x,1) + picture_name)
end