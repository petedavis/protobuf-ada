# Extra settings for GNATStudio
import GPS
from gs_utils import hook

# some_worker = None

#GPS.Preference(
#    "Plugins/auto_highlight_occurrences/highlight_selection").create(
#    "Highlight selection", "boolean",
#    "Attempt to highlight the current selection.",
#    True)

@hook('before_exit_action_hook')
def __before_exit():
    """Run before GPS exits"""
    pass


@hook('gps_started')
def __on_gps_started():
#       initialize plugin
    pass
