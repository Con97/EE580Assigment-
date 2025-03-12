fid = fopen('data.h','w');


%% FIR FILTER
%% B
fprintf(fid,['#define N_FIR_B %d' char([13 10])], length(filter_b));
fwrite(fid,char([13 10]),'uchar');

fwrite(fid,'float filter_b[] = { ','uchar');
for ct = 1:length(filter_b)-1
    fprintf(fid,'%.7ff, ', single(filter_b(ct)));
end
fprintf(fid,'%.7ff', single(filter_b(end)));
fwrite(fid,[' };' char([13 10])],'uchar');
fwrite(fid,char([13 10]),'uchar');
%% A
fprintf(fid,['#define N_FIR_A %d' char([13 10])], length(filter_a));
fwrite(fid,char([13 10]),'uchar');
fwrite(fid,'float filter_a[] = { ','uchar');
for ct = 1:length(filter_a)-1
    fprintf(fid,'%.7ff, ', single(filter_a(ct)));
end
fprintf(fid,'%.7ff', single(filter_a(end)));
fwrite(fid,[' };' char([13 10])],'uchar');
fwrite(fid,char([13 10]),'uchar');


fclose(fid);