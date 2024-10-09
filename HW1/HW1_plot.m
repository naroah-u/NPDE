clc,clear
for i = 0:3
    tiledlayout(1, 2, 'TileSpacing', 'compact', 'Padding', 'compact');
    file_name = "data/output_" + i + ".txt";
    table = readmatrix(file_name);
    x = table(:, 1);
    y = table(:, 2:end);
    error = abs(y(:, 2:end) - y(:, 1));

    nexttile
    plot(x, y, 'LineWidth', 2);
    title("m=" + size(x,1), 'FontSize', 14);
    legend('v', 'v_{10}', 'v_{100}', 'FontSize', 14);

    nexttile
    plot(x, error, 'LineWidth', 2);
    title("m=" + size(x,1) + "的误差图像", 'FontSize', 14);
    legend('v_{10}', 'v_{100}', 'FontSize', 14);

    picture_name = ".png";
    if i >= 2 
        picture_name = "修正" + picture_name;
    end
    position = get(gcf, 'Position');
    set(gcf, 'unit', 'centimeters', 'Position', [20 5 20 10]);
    saveas(gcf, "picture/m=" + size(x,1) + picture_name)
end