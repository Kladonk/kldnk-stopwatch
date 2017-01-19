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
    struct obs_frontend_source_list sources = {};
    obs_frontend_get_scenes(&sources);

    obs_source_t *source = NULL;
    size_t i = 0;

    while (!source && i++ < sources.sources.num)
    {
        obs_source_t *scene = sources.sources.array[i];
        if (m_targetScene == scene.name)
        {
            m_targetScene = scene;
        }
    }
    obs_frontend_set_current_source(source);

    obs_frontend_source_list_free(&sources);
}
