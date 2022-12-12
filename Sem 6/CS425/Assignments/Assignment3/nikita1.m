%%% Illustrate AM modulation  using triangl function
%%% Defining message signal as a triangle signal, in real life however, this
%%% could be anything like voice signal etc. that we would want to transmit


%function ExampleAMdemfilt
clear all;
close all;

%%Time specifications:
Fs = 8000;                   % samples per second
dt = 1/Fs;                   % seconds per sample
StopTime = 0.25;             % seconds
t = (0:dt:StopTime-dt)';     % seconds
%%Sine wave:
Fc = 30;                     % hertz
m_sig = cos(2*pi*Fc*t);
Lm_sig=length(m_sig);
Lfft=length(t);   % defining DFT (or FFT) size
Lfft=2^ceil(log2(Lfft))  % making Lfft a power of 2 since this makes the fft algorithm work fast
M_sig=fftshift(fft(m_sig,Lfft))
freqm=(-Lfft/2:Lfft/2-1)/(Lfft*dt)
%%% AM modulation
fc=200; % carrier frequency
ka=0.5;
s_am=(1+ka*m_sig).*cos(2*pi*fc*t) % recall AM modulation works by multiplying message signal by a cos function at the carrier frequency and adding a unmodulated carrier
Lfft=length(t)
Lfft=2^ceil(log2(Lfft)+1) % increasing fft size by another factor of 2
S_am=fftshift(fft(s_am,Lfft)); % obtaining frequency domain modulated signal
freqs=(-Lfft/2:Lfft/2-1)/(Lfft*dt) % Defining the frequency axis for the frequency domain DSB modulated signal

 
Trange=[0 0.25 -2 2] % This specifies the range of axis for the plot, the first two parameters are range limits for x-axis, and last two parameters are for y-axis
Frange=[-700 700 0 300] % axis range for frequency domain plots
figure(1)
subplot(221); plot(t,m_sig)
axis(Trange) % set x-axis and y-axis limits 
title('m\_sig')

subplot(222); plot(t,s_am)
hold on;
plot(t,1+ka*m_sig, 'r:')
plot(t,-1-ka*m_sig, 'r:')
axis(Trange)
title('s\_am')

figure(2)
subplot(221); plot(freqm,abs(M_sig))
axis(Frange) % set x-axis and y-axis limits 
title('M\_sig')

subplot(222); plot(freqs,abs(S_am))
axis(Frange)
title('S\_am')
