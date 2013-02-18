fdir = 'res/';
ftrace = 'mcf';
fnum = 11;
ffetch = 'eager';
frep = 'fifo';
fnamebase=[fdir ftrace num2str(fnum) ffetch frep];
fname = [fnamebase '.res'];
fout = [fnamebase '.png'];
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
res = in(:,find(in(3,:) == min(min(Z))));
r2 = num2cell(res);
[B, S, AAT] = deal(r2{:});
Z = log(log(Z));
mz = max(max(Z))+1;
h = figure;
surf(X, Y, Z);
text(mx, my/2, mz, ["Minimum B = " num2str(B)]);
text(mx, my/2, mz-.2, ["Minimum S = " num2str(S)]);
text(mx, my/2, mz-.4, ["Minimum AAT = " num2str(AAT)]);
saveas(h, fout);
