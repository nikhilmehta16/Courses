clear all
close all


% ( ExampleFM .m) 
% This program uses triangl.m to i l lustrate frequency modulation 
% and demodulation


ts=1.e-4 ; 
t=-0.04:ts:0.04; 
Ta= 0.01; 
m_sig=triangl(( t + 0.01 ) / Ta) - triangl(( t - 0.01 ) / Ta ) ; 
Lfft=length(t) ; Lfft=2^ceil( log2 ( Lfft ) ); 
M_fre=fftshift( fft ( m_sig , Lfft ) ); 
reqm= ( -Lfft / 2 : Lfft/2- 1 ) / ( Lfft*ts ) ; 
B_m=100 ; %Bandwidth of the signal is B_m Hz . 
% Design a s imple l owpass filter with bandwidth B_m Hz . 
%h= firl(80, [ B_m* ts ]); 
% 
kf=600*pi ; 
kp = 10;

m_intg=kf*ts* cumsum(m_sig) ; 
s_fm=cos (2*pi*300*t + m_intg ) ; 
s_pm=cos (2*pi*300*t + kp*pi*m_sig ) ; 
Lfft=length(t) ; Lfft=2^ceil( log2 ( Lfft ) ); 
S_fm= fftshift ( fft ( s_fm , Lfft ) ); 
S_pm= fftshift ( fft ( s_pm , Lfft ) ); 
freqs = ( -Lfft / 2 : Lfft/2- 1 ) / ( Lfft*ts ) ; 
s_fmdem=diff ( [ s_fm(1) s_fm] ) / ts /kf ; 
s_fmrec= s_fmdem .*( s_fmdem > 0) ; 
%s_dec=filter (h, 1 , s_fmrec ); 

% Demodulation 
% Using an ideal LPF wi th bandwidth 200 Hz 
Trange1 = [ -0.04 0.04 -1.2 1.2] ; 
figure(1) 
subplot (311) ; m1 =plot (t,m_sig) ; 
axis ( Trange1 ) ; set (m1 , 'Linewidth' ,2) ; 
xlabel ( ' t (sec) '); ylabel ( ' m(t) '); 
title ( ' Message signal '); 
%subplot (212 ) ; m2 =plot (t, s_dec ) ; 
%set ( m2, ' Linewidth ' ,2) ; 
%xlabel ( ' { \ it t } ( sec ) '); ylabel ( ' { \ it m}_d({\ it t } ) ' ) 
%title ( ' demodulated FM signal ');


%figure(2) 
subplot (312) ; tdl=plot (t, s_fm) ; 
axis ( Trange1 ); set ( tdl , 'Linewidth' ,2) ; 
xlabel ( 't (sec)'); ylabel ( ' s\_FM(t) ') 
title ( ' FM signal '); 
subplot (313 ) ; td2 =plot (t, s_pm) ; 
axis ( Trange1 ) ; set ( td2 , 'Linewidth' ,2) ; 
xlabel ( 't (sec)'); ylabel ( ' s\_PM(t) ') 



Frange= [ -600 600 0 300] ; 
figure (4) 
subplot (211) ; fdl=plot ( freqs , abs ( S_fm) ); 
axis(Frange) ; set ( fdl , 'Linewidth' ,2) ; 
xlabel ( 'f(Hz)'); ylabel ( 'S_FM(f)') 
title ( ' FM ampli tude spectrum ' ); 
subplot (212) ; fd2 =plot ( freqs,abs ( S_pm) ) ; 
axis(Frange) ; set ( fd2 , 'Linewidth' ,2) ; 
xlabel ( 'f(Hz)'); ylabel ( 'S_PM(f)') 
title ( ' PM ampli tude spec t rum ' ); 


function y = triangl(t)
y=(1-abs(t)).*(t>=-1).*(t<1); % i.e. setting y to 1 -|t|  if  |t|<1 and to 0 if not
end

