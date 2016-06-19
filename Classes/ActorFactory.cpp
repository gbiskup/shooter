#include "ActorFactory.h"

GameActor * ActorFactory::createActorOfType(ActorType actorType)
{
	GameActor * actor;
	switch (actorType)
	{
		case ActorType::HERO:
			actor = static_cast<GameActor*>( createHero() );
			break;

		default:
		case ActorType::MONSTER:
			break;
	}
	return actor;
}

GameActor * ActorFactory::createHero()
{

}

