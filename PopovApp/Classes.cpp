#pragma once
#include "pch.h"
#include "Classes.h"
#include <iostream>
#include "probdist.h"
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include "windows.h"
#include <random>

using namespace std;
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0, 1);

Sample::Sample(int s) :sampSize(s) {
	samp = new int[sampSize] {0};
}
int Sample::GetSampAt(int i) { return samp[i]; };
int Sample::GetSampSize() { return sampSize; };

Sample_1::Sample_1(int size) : Sample(size) {}
Sample_2::Sample_2(int size) : Sample(size) {}

Sample::~Sample() {
	delete[] samp;
}

void Sample_1::Simulate(double lambda) {
	for (size_t i = 0; i < sampSize; ++i)
	{
		int k = 0;
		double t = exp(-lambda), s = t;
		double x = dis(gen);	
		while (x > s) {
			++k;
			t *= lambda / k;
			s += t;
		}
		samp[i] = k;
	}
}

void Sample_2::Simulate(double lambda) {
	double l = exp(-lambda);
	for (size_t i = 0; i < sampSize; ++i)
	{
		int k = 0;
		double t = dis(gen);
		while (t > l)
		{
			t *= dis(gen);
			++k;
		}
		samp[i] = k;
	}
}

Distribution::Distribution(double l):lambda(l){
	Freqsize = 3 + lambda + 3 * sqrt(lambda);
	expProb = new double[Freqsize] {0};	
	double prob = exp(-lambda);
	double sum = 1;
	double epsilon = 1e-6;
	int j = 0;
	for (; sum > epsilon && j < Freqsize - 1; ++j)
	{
		sum -= prob;
		expProb[j] = prob;
		prob *= lambda/ (j + 1);
	}
	expProb[j] += sum;
}

double Distribution::GetExpProbAt(int i) { return expProb[i]; };
double Distribution::GetLambda() { return lambda; };
void Distribution::SetLambda(double l) { lambda = l; };
int Distribution::GetFreqsize() { return Freqsize; };


Distribution::~Distribution()
{
	delete[] expProb;
};

double ChiSq::GetPvalue() { return pvalue; };
double ChiSq::GetExpFreqAt(int i) { return expFreq[i]; };
int ChiSq::GetObsFreqAt(int i) { return obsFreq[i]; };
int ChiSq::GetFreqsize() { return Freqsize; };

void ChiSq::calculatePvalue() {
	xi = 0;
	int bd = Freqsize;
	double* expFreqGrouped = new double[bd] {0};
	double* obsFreqGrouped = new double[bd] {0};
	int k = 0;
	for (int i = 0; i < bd; ++i)
	{
		if (expFreqGrouped[k] > 5)
			++k;
		expFreqGrouped[k] += expFreq[i];
		obsFreqGrouped[k] += obsFreq[i];
	}
	if (expFreqGrouped[k] < 5)
	{
		expFreqGrouped[k - 1] += expFreqGrouped[k];
		obsFreqGrouped[k - 1] += obsFreqGrouped[k];
		df = k;
	}
	else df = k + 1;
	for (int i = 0; i < df; ++i)
		xi += pow(obsFreqGrouped[i] - expFreqGrouped[i], 2) / (expFreqGrouped[i]);
	pvalue = 1 - pChi(xi, df - 1);
	delete[] expFreqGrouped;
	delete[] obsFreqGrouped;
}

ChiSq::ChiSq(Distribution* d, Sample* s):Freqsize(d->GetFreqsize()){
	expFreq = new double[Freqsize];
	for (size_t i = 0; i < Freqsize; ++i)
		expFreq[i] = d->GetExpProbAt(i) * s->GetSampSize();
	obsFreq = new int[Freqsize];
	Update(s);
}

void ChiSq::Update(Sample* s) {
	memset(obsFreq, 0, sizeof(int) *Freqsize);
	for (int i = 0; i < s->GetSampSize(); ++i)
		++obsFreq[min(s->GetSampAt(i),Freqsize - 1)];
};

ChiSq::~ChiSq() { delete[] obsFreq; delete[] expFreq;}

