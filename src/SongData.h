#pragma once
#include <string>
#include <vector>

// Information d'une piste
struct TrackData
{
		TrackData() = default;
		TrackData(std::string n, std::string f, double v, double p):
			name(n),
			file(f),
			volume(v),
			pan(p)
		{

		}

		std::string name;
		std::string file;
		double volume;
		double pan;
};

// Information pour le morceau entier
struct SongData
{
		std::vector<TrackData> tracks{};
		int tempo{};
		std::string name{};
};
