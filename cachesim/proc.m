fdir = '';
ftrace = 'perlbench';
fnum = 0:15;
ffetch = 'BE';
frep = 'LN';
fout = [fdir ftrace '.out'];
ro = 1;
for fet = ffetch
for rep = frep
for n = fnum
fnamebase=[fdir ftrace fet rep num2str(n)];
fname = [fnamebase '.res'];
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
C(ro+n,1) = fet;
D(ro+n,1) = rep;
A(ro+n, 1:4) = [n; B; S; AAT];
end
ro += 16;
end
end
pos = A(:,4) == min(A(:,4));
printf('Best for %s is (C:%d,B:%d,S:%d,F:%s,R:%s) with AAT of %f', ftrace, A(pos,1), A(pos,2), A(pos,3), C(pos,1), D(pos,1), A(pos,4))
