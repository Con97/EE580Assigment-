fid = fopen('data.h','w');


%% LP IIR FILTER
%% B
fprintf(fid,['#define N_FIR_B %d' char([13 10])], length(LP_B));
fwrite(fid,char([13 10]),'uchar');

fwrite(fid,'float LP_B[] = { ','uchar');
for ct = 1:length(LP_B)-1
    fprintf(fid,'%.7ff, ', single(LP_B(ct))); % Using single precision
end
fprintf(fid,'%.7ff', single(LP_B(end))); % Final coefficient
fwrite(fid,[' };' char([13 10])],'uchar');
fwrite(fid,char([13 10]),'uchar');
%% A
fprintf(fid,['#define N_FIR_A %d' char([13 10])], length(LP_A));
fwrite(fid,char([13 10]),'uchar');
fwrite(fid,'float LP_A[] = { ','uchar');
for ct = 1:length(LP_A)-1
    fprintf(fid,'%.7ff, ', single(LP_A(ct))); % Using single precision
end
fprintf(fid,'%.7ff', single(LP_A(end))); % Final coefficient
fwrite(fid,[' };' char([13 10])],'uchar');
fwrite(fid,char([13 10]),'uchar');

%% BP IIR FILTER
%% B
fprintf(fid,['#define N_FIR_B %d' char([13 10])], length(BP_B));
fwrite(fid,char([13 10]),'uchar');

fwrite(fid,'float BP_B[] = { ','uchar');
for ct = 1:length(BP_B)-1
    fprintf(fid,'%.7ff, ', single(BP_B(ct))); % Using single precision
end
fprintf(fid,'%.7ff', single(BP_B(end))); % Final coefficient
fwrite(fid,[' };' char([13 10])],'uchar');
fwrite(fid,char([13 10]),'uchar');
%% A
fprintf(fid,['#define N_FIR_A %d' char([13 10])], length(BP_A));
fwrite(fid,char([13 10]),'uchar');
fwrite(fid,'float BP_A[] = { ','uchar');
for ct = 1:length(BP_A)-1
    fprintf(fid,'%.7ff, ', single(BP_A(ct))); % Using single precision
end
fprintf(fid,'%.7ff', single(BP_A(end))); % Final coefficient
fwrite(fid,[' };' char([13 10])],'uchar');
fwrite(fid,char([13 10]),'uchar');

%% HP IIR FILTER
%% B
fprintf(fid,['#define N_FIR_B %d' char([13 10])], length(HP_B));
fwrite(fid,char([13 10]),'uchar');

fwrite(fid,'float HP_B[] = { ','uchar');
for ct = 1:length(HP_B)-1
    fprintf(fid,'%.7ff, ', single(HP_B(ct))); % Using single precision
end
fprintf(fid,'%.7ff', single(HP_B(end))); % Final coefficient
fwrite(fid,[' };' char([13 10])],'uchar');
fwrite(fid,char([13 10]),'uchar');
%% A
fprintf(fid,['#define N_FIR_A %d' char([13 10])], length(HP_A));
fwrite(fid,char([13 10]),'uchar');
fwrite(fid,'float HP_A[] = { ','uchar');
for ct = 1:length(HP_A)-1
    fprintf(fid,'%.7ff, ', single(HP_A(ct))); % Using single precision
end
fprintf(fid,'%.7ff', single(HP_A(end))); % Final coefficient
fwrite(fid,[' };' char([13 10])],'uchar');
fwrite(fid,char([13 10]),'uchar');


fclose(fid);