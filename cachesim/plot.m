fdir = 'res/';
fresdir = 'imgs';
if length(argv) != 4
	error('Arguments: <trace_file_name> <trial_number(0..15)> <fetch_policy(B,E)> <replacement_policy(L,N)>')
end
ftrace = argv(){1};
fnum = argv(){2};
ffetch = argv(){3};
frep = argv(){4};
fnamebase=[ftrace ffetch frep num2str(fnum)];
fname = [fdir fnamebase '.res'];
fout = [fresdir fnamebase '.png'];
in = transpose(dlmread(fname));
mx = 0;
my = 0;
mx = max(in(1,:))+1;
my = max(in(2,:))+1;
Z = zeros(mx,my)+10000;
X = transpose(1:mx);
Y = transpose(1:my);
for line = in
	Z(line(1)+1,line(2)+1)=line(3);
end
res = in(:,in(3,:) == min(min(Z)));
r2 = num2cell(res);
[B, S, AAT] = deal(r2{:});

Z = log(log(Z));
mz = max(max(Z))+1;
h = figure;
surf(X, Y, Z);
title([ftrace " C:" num2str(fnum)]);
text(mx, my/2, mz, ["Minimum B = " num2str(B)]);
text(mx, my/2, mz-.2, ["Minimum S = " num2str(S)]);
text(mx, my/2, mz-.4, ["Minimum AAT = " num2str(AAT)]);
saveas(h, fout);
