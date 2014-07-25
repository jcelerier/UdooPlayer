#pragma once
#include <string>
#include <vector>

// Information d'une piste
struct TrackData
{
		TrackData() = default;
		TrackData(TrackData&&) = default;
		TrackData(const TrackData&) = delete;

		TrackData(const std::string n,
				  const std::string f,
				  const double v,
				  const double p):
			name(n),
			file(f),
			volume(v),
			pan(p)
		{

		}

		TrackData& operator=(TrackData&&) = default;
		TrackData& operator=(const TrackData&) = delete;
		const std::string name{};
		const std::string file{};
		const double volume{};
		const double pan{};
};

// Information pour le morceau entier
struct SongData
{
		SongData() = default;
		SongData(SongData&&) = default;
		SongData& operator=(SongData&&) = default;

		std::vector<TrackData> tracks{};
		int tempo{};
		std::string name{};
		int sigNumerateur{};
		int sigDenominateur{};
};
