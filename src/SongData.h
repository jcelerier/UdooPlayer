#pragma once
#include <string>
#include <vector>
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

class SongData
{
	public:
		SongData();

		std::vector<TrackData> tracks{};
};
