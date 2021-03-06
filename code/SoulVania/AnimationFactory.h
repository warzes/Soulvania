#pragma once

#include "Animation.h"

using AnimationDict = std::map<std::string, Animation>;

const auto NULL_ANIMATION = Animation{ "", 0 };

class AnimationFactory
{
public:
	AnimationFactory(AnimationDict animations);

	Animation Create(); // Return the default (first) animation
	Animation Create(std::string name);

	// Create a new animation factory from a subset animation of this factory
	std::shared_ptr<AnimationFactory> Clone(std::vector<std::string> animationNames);

	AnimationDict GetAnimations();

private:
	AnimationDict animations;
};