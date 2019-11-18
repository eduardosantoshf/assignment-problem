%% Histograma para n = 13

% 93150
fileID = fopen('n_13_93150.txt');
mydata = textscan(fileID, '%f%f'); %separa as duas colunas por tab
md1 = mydata{1,1}; %coluna 1 (custos)
md2 = mydata{1,2}; %coluna 2 (número de ocorrências)
fclose(fileID);

figure(1);
bar(md1, md2); %histograma 
hold on;

%calculo da Gaussiana normal
media = sum(md2.*md1)/sum(md2);
variancia = (sum(md2.*(md1-media).^2))/sum(md2);
desvio = sqrt(variancia);
x= md1;
y = exp((-(x-media).^2)/(2*desvio^2)) * max(md2);

plot(x,y, 'r', 'LineWidth', 2); %plot da Gaussiana
set(gca,'FontSize',20);
xlabel('Custo', 'FontSize', 20);
ylabel('Número de assignments' , 'FontSize', 20);
title('Seed: 93150, n = 13', 'FontSize', 20);
legend('Valores obtidos', 'Gaussiana normal', 'FontSize', 20);
hold off;

% 93107
fileID = fopen('n_13_93107.txt');
mydata = textscan(fileID, '%f%f'); %separa as duas colunas por tab
md1 = mydata{1,1}; %coluna 1 (custos)
md2 = mydata{1,2}; %coluna 2 (número de ocorrências)
fclose(fileID);

figure(2);
bar(md1, md2);
hold on;

%calculo da Gaussiana normal
media = sum(md2.*md1)/sum(md2);
variancia = (sum(md2.*(md1-media).^2))/sum(md2);
desvio = sqrt(variancia);
x= md1;
y = exp((-(x-media).^2)/(2*desvio^2)) * max(md2);

plot(x,y, 'r', 'LineWidth', 2); %plot da Gaussiana 
set(gca,'FontSize',20);
xlabel('Custo', 'FontSize', 20);
ylabel('Número de assignments' , 'FontSize', 20);
title('Seed: 93107, n = 13', 'FontSize', 20);
legend('Valores obtidos', 'Gaussiana normal', 'FontSize', 20);
hold off;

% 88903
fileID = fopen('n_13_88903.txt');
mydata = textscan(fileID, '%f%f'); %separa as duas colunas por tab
md1 = mydata{1,1}; %coluna 1 (custos)
md2 = mydata{1,2}; %coluna 2 (número de ocorrências)
fclose(fileID);

figure(3);
bar(md1, md2);
hold on;

%calculo da Gaussiana normal
media = sum(md2.*md1)/sum(md2);
variancia = (sum(md2.*(md1-media).^2))/sum(md2);
desvio = sqrt(variancia);
x= md1;
y = exp((-(x-media).^2)/(2*desvio^2)) * max(md2);

plot(x,y, 'r', 'LineWidth', 2); %plot da Gaussiana
set(gca,'FontSize',20);
xlabel('Custo', 'FontSize', 20);
ylabel('Número de assignments' , 'FontSize', 20);
title('Seed: 88903, n = 13', 'FontSize', 20);
legend('Valores obtidos', 'Gaussiana normal', 'FontSize', 20);
hold off;

%% Histograma para n = 14

% 93150
fileID = fopen('n_14_93150.txt');
mydata = textscan(fileID, '%f%f'); %separa as duas colunas por tab
md1 = mydata{1,1}; %coluna 1 (custos)
md2 = mydata{1,2}; %coluna 2 (número de ocorrências)
fclose(fileID);

figure(4);
bar(md1, md2);
hold on;

%calculo da Gaussiana normal
media = sum(md2.*md1)/sum(md2);
variancia = (sum(md2.*(md1-media).^2))/sum(md2);
desvio = sqrt(variancia);
x= md1;
y = exp((-(x-media).^2)/(2*desvio^2)) * max(md2);

plot(x,y, 'r', 'LineWidth', 2); %plot da Gaussiana
set(gca,'FontSize',20);
xlabel('Custo', 'FontSize', 20);
ylabel('Número de assignments' , 'FontSize', 20);
title('Seed: 93150, n = 14', 'FontSize', 20);
legend('Valores obtidos', 'Gaussiana normal', 'FontSize', 20);
hold off;

% 93107
fileID = fopen('n_14_93107.txt');
mydata = textscan(fileID, '%f%f'); %separa as duas colunas por tab
md1 = mydata{1,1}; %coluna 1 (custos)
md2 = mydata{1,2}; %coluna 2 (número de ocorrências)
fclose(fileID);

figure(5);
bar(md1, md2);
hold on;

%calculo da Gaussiana normal
media = sum(md2.*md1)/sum(md2);
variancia = (sum(md2.*(md1-media).^2))/sum(md2);
desvio = sqrt(variancia);
x= md1;
y = exp((-(x-media).^2)/(2*desvio^2)) * max(md2);

plot(x,y, 'r', 'LineWidth', 2); %plot da Gaussiana
set(gca,'FontSize',20);
xlabel('Custo', 'FontSize', 20);
ylabel('Número de assignments' , 'FontSize', 20);
title('Seed: 93107, n = 14', 'FontSize', 20);
legend('Valores obtidos', 'Gaussiana normal', 'FontSize', 20);
hold off;

% 88903
fileID = fopen('n_14_88903.txt');
mydata = textscan(fileID, '%f%f'); %separa as duas colunas por tab
md1 = mydata{1,1}; %coluna 1 (custos)
md2 = mydata{1,2}; %coluna 2 (número de ocorrências)
fclose(fileID);

figure(6);
bar(md1, md2);
hold on;

%calculo da Gaussiana normal
media = sum(md2.*md1)/sum(md2);
variancia = (sum(md2.*(md1-media).^2))/sum(md2);
desvio = sqrt(variancia);
x= md1;
y = exp((-(x-media).^2)/(2*desvio^2)) * max(md2);

plot(x,y, 'r', 'LineWidth', 2); %plot da Gaussiana
set(gca,'FontSize',20);
xlabel('Custo', 'FontSize', 20);
ylabel('Número de assignments' , 'FontSize', 20);
title('Seed: 88903, n = 14', 'FontSize', 20);
legend('Valores obtidos', 'Gaussiana normal', 'FontSize', 20);
hold off;

%% Gráfico que compara custos mínimos com custos máximos

% 93150
f = fopen('93150_custos_minimos.txt', 'r');
formatSpec = '%f';
custos_minimos = fscanf(f, formatSpec);
fclose(f);

f = fopen('93150_custos_maximos.txt', 'r');
formatSpec = '%f';
custos_maximos = fscanf(f, formatSpec);
fclose(f);

figure(7);
n = [1:14]; %valores de n
ylim([0 max(custos_maximos)]);
plot(n , custos_minimos, n, custos_maximos, 'LineWidth', 2); %plot dos custos mínimos e máximos
set(gca,'FontSize',20);
legend('Custo mínimo', 'Custo máximo', 'FontSize', 20);
xlabel('n', 'FontSize', 20);
ylabel('Custo', 'FontSize', 20);
title('Seed: 93150', 'FontSize', 20);
grid;

% 93107
f = fopen('93107_custos_minimos.txt', 'r');
formatSpec = '%f';
custos_minimos = fscanf(f, formatSpec);
fclose(f);

f = fopen('93107_custos_maximos.txt', 'r');
formatSpec = '%f';
custos_maximos = fscanf(f, formatSpec);
fclose(f);

figure(8);
n = [1:14]; %valores de n
ylim([0 max(custos_maximos)]);
plot(n , custos_minimos, n, custos_maximos, 'LineWidth', 2); %plot dos custos mínimos e máximos
set(gca,'FontSize',20);
legend('Custo mínimo', 'Custo máximo', 'FontSize', 20);
xlabel('n', 'FontSize', 20);
ylabel('Custo', 'FontSize', 20);
title('Seed: 93107', 'FontSize', 20);
grid;

% 88903
f = fopen('88903_custos_minimos.txt', 'r');
formatSpec = '%f';
custos_minimos = fscanf(f, formatSpec);
fclose(f);

f = fopen('88903_custos_maximos.txt', 'r');
formatSpec = '%f';
custos_maximos = fscanf(f, formatSpec);
fclose(f);

figure(9);
n = [1:14]; %valores de n
ylim([0 max(custos_maximos)]);
plot(n , custos_minimos, n, custos_maximos, 'LineWidth', 2); %plot dos custos mínimos e máximos
set(gca,'FontSize',20);
legend('Custo mínimo', 'Custo máximo', 'FontSize', 20);
xlabel('n', 'FontSize', 20);
ylabel('Custo', 'FontSize', 20);
title('Seed: 88903', 'FontSize', 20);
grid;

%% Tempo de execução dos3 algoritmos 

%93150
f = fopen('93150_cputime_bf.txt', 'r');
formatSpec = '%f';
cpu_time_bf = fscanf(f, formatSpec);
fclose(f);

f = fopen('93150_cputime_BnB.txt', 'r');
formatSpec = '%f';
cpu_time_bnb = fscanf(f, formatSpec);
fclose(f);

f = fopen('93150_cputime_RandomPerm.txt', 'r');
formatSpec = '%f';
cpu_time_randomperm = fscanf(f, formatSpec);
fclose(f);

figure(10);
n = [1:14]; %valores de n
%igual a plot mas escala de y é logarítmica
semilogy(n , cpu_time_bf, n, cpu_time_bnb, n, cpu_time_randomperm, 'g', 'LineWidth', 2 );
set(gca,'FontSize',20);
legend('Brute force', 'Branch And Bound', 'Random Permutations','FontSize',20);
xlabel('n','FontSize',20);
ylabel('CPU time (sec)','FontSize',20);
title('Seed: 93150','FontSize',20);
grid;

%93107
f = fopen('93107_cputime_bf.txt', 'r');
formatSpec = '%f';
cpu_time_bf = fscanf(f, formatSpec);
fclose(f);

f = fopen('93107_cputime_BnB.txt', 'r');
formatSpec = '%f';
cpu_time_bnb = fscanf(f, formatSpec);
fclose(f);

f = fopen('93107_cputime_RandomPerm.txt', 'r');
formatSpec = '%f';
cpu_time_randomperm = fscanf(f, formatSpec);
fclose(f);

figure(11);
n = [1:14];%valores de n
%igual a plot mas escala de y é logarítmica
semilogy(n , cpu_time_bf, n, cpu_time_bnb, n, cpu_time_randomperm, 'g', 'LineWidth', 2 );
set(gca,'FontSize',20);
legend('Brute force', 'Branch And Bound', 'Random Permutations','FontSize',20);
xlabel('n','FontSize',20);
ylabel('CPU time (sec)','FontSize',20);
title('Seed: 93107','FontSize',20);
grid;

%88903
f = fopen('88903_cputime_bf.txt', 'r');
formatSpec = '%f';
cpu_time_bf = fscanf(f, formatSpec);
fclose(f);

f = fopen('88903_cputime_BnB.txt', 'r');
formatSpec = '%f';
cpu_time_bnb = fscanf(f, formatSpec);
fclose(f);

f = fopen('88903_cputime_RandomPerm.txt', 'r');
formatSpec = '%f';
cpu_time_randomperm = fscanf(f, formatSpec);
fclose(f);

figure(12);
n = [1:14];%valores de n
%igual a plot mas escala de y é logarítmica
semilogy(n , cpu_time_bf, n, cpu_time_bnb, n, cpu_time_randomperm, 'g', 'LineWidth', 2 );
set(gca,'FontSize',20);
legend('Brute force', 'Branch And Bound', 'Random Permutations','FontSize',20);
xlabel('n','FontSize',20);
ylabel('CPU time (sec)','FontSize',20);
title('Seed: 88903','FontSize',20);
grid;
