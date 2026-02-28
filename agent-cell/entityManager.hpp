//#pragma once
//
//#include <queue>
//#include <iostream>
//#include <array>
//#include <cassert>
//
//#include "entity.hpp"
//#include "config.hpp"
//
//class EntityManager {
//public:
//	EntityManager() {
//		for (Entity entity = 0; entity < Config::MAX_ENTITIES; ++entity) {
//			mAvailableEntities.push(entity);
//		}
//	}
//
//	Entity CreateEntity() {
//		assert(mLivingEntityCount < Config::MAX_ENTITIES && "Too many entities inexistance.");
//
//		Entity id = mAvailableEntities.front();
//		mAvailableEntities.pop();
//		++mLivingEntityCount;
//
//		return id;
//	}
//
//	Entity DestroyEntity(Entity entity) {
//		assert(entity < Config::MAX_ENTITIES && "Entity out of range.");
//
//		mSignatures[entity].reset();
//		mAvailableEntities.push(entity);
//		--mLivingEntityCount;
//	}
//
//	Signature GetSignature(Entity entity) {
//		assert(entity < Config::MAX_ENTITIES && "Entity out of range.");
//		
//		return mSignatures[entity];
//	}
//
//private:
//	std::queue<Entity> mAvailableEntities{};
//	std::array<Signature, Config::MAX_ENTITIES> mSignatures{};
//	uint32_t mLivingEntityCount{};
//};
