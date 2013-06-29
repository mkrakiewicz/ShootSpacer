#ifndef VERSION_H_
#define VERSION_H_


/**
 * BASIC STUCTURE OF THE VERSION:
 * 		"V.S.R rcRC"
 * 		or "V.S.R" if current RC == 0
 * 		V - main version - incremented by adding tag: nextversion (check pre-commit hook to make sure).
 * 			Incremented when a lot of issues were fixed, or some major enhancements were fixed... or simply it is ready
 * 			to be called Version Two. :P
 * 		S - sub version - incremented by adding tag: subversion
 * 			Incremented when some feature was implemented, or major bug fixed.
 * 		R - release - incremented by adding tag: release
 * 			Incremented when a task or an issue were completed, bug fixed... etc
 * 		RC - release candidate
 * 			Incremented after each commit. It's a number of commits since last release.
 *
 * 		All variables are calculated by summing up the number of tags since last "higher level tag":
 * 			V - all tags, S - all tags since last V, R - all tags since last S, RC - all commits since last R
 *
 */

namespace VERSION_INFO {

#include "version"

const irr::core::stringw CURRENT_VERSION_STRING = irr::core::stringw("v")
		+ VERSION;
}

#endif
