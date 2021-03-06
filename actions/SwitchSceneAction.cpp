/******************************************************************************
    Kladonk Stopwatch Plugin
    Copyright(C) 2016-2017 Jan Held <development@kladonk.de>

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "SwitchSceneAction.h"
#include <util/util.hpp>
#include <../UI/obs-frontend-api/obs-frontend-api.h>

void SwitchSceneAction::execute()
{
    if (m_targetScene.empty())
    {
        return;
    }

    obs_source_t *scene = obs_get_source_by_name(m_targetScene.c_str());
    obs_source_t *currentScene = obs_frontend_get_current_scene();
    if (scene && scene != currentScene)
    {
        obs_frontend_set_current_scene(scene);
    }
    obs_source_release(scene);
    obs_source_release(currentScene);
}
