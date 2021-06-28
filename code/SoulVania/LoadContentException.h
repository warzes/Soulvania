#pragma once

struct LoadContentException : public std::runtime_error
{
	LoadContentException(std::string const& message) : std::runtime_error(message) {}
};