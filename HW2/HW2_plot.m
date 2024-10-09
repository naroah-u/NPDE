clc,clear
dt_s = [0.01 0.03];
for i = 1:2
    tiledlayout(1, 2, 'TileSpacing', 'compact', 'Padding', 'compact');
    file_name = "data/问题" + i + ".txt";
    table = readmatrix(file_name);
    x = table(1, :);
    v = table(2:end, :);
    u = sin(2*pi*(x+0.3));
    error = abs(u - v);

    nexttile
    plot(x, [v;u], 'LineWidth', 2);
    title("解图像", 'FontSize', 14);
    legend('离散方程A', '离散方程B', '准确解', 'Location', 'northwest', 'FontSize', 14);

    nexttile
    plot(x, error, 'LineWidth', 2);
    title("误差图像", 'FontSize', 14);
    legend('离散方程A', '离散方程B', 'Location', 'northwest', 'FontSize', 14);

    position = get(gcf, 'Position');
    set(gcf, 'unit', 'centimeters', 'Position', [20 5 20 10]);
    saveas(gcf, "picture/问题" + i + ".png")
end