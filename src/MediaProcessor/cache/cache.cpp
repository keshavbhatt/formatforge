#include "cache.h"

Cache::Cache() {}

Cache &Cache::instance() {
  static Cache instance;
  return instance;
}
