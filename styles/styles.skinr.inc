<?php

/**
 * @file
 * Implementation of a Skinr plugin.
 *
 * @todo Decide on the naming convention for this style. This depends on whether
 * or not CTools will handle the plugin functionality. Currently proposed
 * naming convention which doesn't use CTools, is PLUGINNAME.skinr.inc. 
 */

/**
 * Implements hook_skinr_info().
 *
 * Define the API version of this Skinr plugin. This is required when
 * creating a new Skinr plugin. It checks to make sure your Skins are compatible
 * with the installed version of Skinr.
 *
 * The "hook" prefix is substituted with the name of the module or theme that
 * implements it, e.g. THEMENAME_PLUGINNAME_skinr_info(), or
 * MODULENAME_PLUGINNAME_skinr_info().
 *
 * The plugin will inherit information such as what version of core it applies
 * to from the module or theme implementing it.
 *
 * @todo We are not sure this will be necessary, if we do not end up using
 * and external too such as CTools to handle plugin functionality. If we do use
 * CTools, it will be required and will need to contain more information.
 */
function skinr_styles_skinr_info() {
  return array('skinr api' => '2.0');
}

/**
 * Implements hook_skinr_groups().
 *
 * Optional. Defines group(s) that will contain skins. Groups are form element
 * containers used to organize skins categorically using vertical_tabs. If you
 * don't define a group, your skins will appear in Skinr's default group, which
 * is labeled "General."
 *
 * Group name(s):
 * Each group name must be unique. It is recommended to prefix the name of each
 * group with the name of the theme or module name implementing it, followed by
 * the name of the group. Note that you cannot define 2 groups with the same
 * the same name, even if they are in different plugins.
 *
 * Group properties:
 * - #title (required): Brief title of the tab.
 * - #description (optional): Description of the tab group.
 * - #weight (discouraged): Weight of the tab group; NULL by default.
 * - #admin_title (recommended): Administrative title of the group, displayed on
 *   the "Manage Skins" page.
 * - #admin_description (recommended): Administrative description of the group
 *   and a technical description of the skins it contains for the "Manage skins"
 *   page.
 * - #screenshot (optional): The path to an image containing a screenshot of the
 *   skin, which will be used in the "Manage Skins" page. Defaults to
 *   $path_to_plugin/screenshot.png, so only needs to be specified if different.
 *
 * The "hook" prefix is substituted with the name of the module or theme that
 * implements it, followed by the plugin name, e.g.
 * THEMENAME_PLUGINNAME_skinr_groups(), or MODULENAME_PLUGINNAME_skinr_groups().
 *
 *
 * @todo Create Skinr's default group implementation. Skinr will provide a
 * plugin containing groups to provide some consistency in the UI, promote the
 * re-use of groups as categories, and ease the burden of creating skins.
 * @todo Document that collapsible/collapsed options are obsolete for groups in
 * the new version.
 */
function skinr_styles_skinr_groups() {
  $groups['skinr_typography'] = array(
    '#title' => t('Typography'),
    '#description' => t('Choose one or more styles to apply to content of this element.'),
    '#admin_title' => t('Skinr content styles'),
    '#admin_description' => t('Contains 3 @font-face fonts (Droid Sans, Fontin Sans and Museo) that style headings, and font sizing options designed for a base font-size of 13px.'),
  );
  return $groups;
}

/**
 * Implements hook_skinr_skins().
 *
 * Required. Define the skin(s) for this Skinr plugin. Each skin definition
 * consists of properties that define its form element and settings that are
 * needed to make it work, such as the class(es) Skinr should apply, which files
 * it should load, whether or not it should be disabled by default and which
 * theme hook(s) it was designed to work with.
 *
 * Skin name(s):
 * Each skin name must be unique. It is recommended to prefix the name of each
 * group with the name of the theme or module name implementing it, followed by
 * the name of the group. Note that you cannot define 2 groups with the same
 * the same name, even if they are in different plugins.
 *
 * Skin settings:
 * - #title (required): Label of the skin form element.
 * - #description (optional): End-user facing description of the skin.
 * - #group (optional): The group the skin is attached to; defaults to a Skinr
 *   provided group.
 * - #type (optional): The type of form element. Allowed values:
 *   - checkboxes (default): For single and multiple options. Does not need to
 *     be set manually, as Skinr will apply this by default.
 *   - select: A single option can be chosen, but many exist.
 *   - radios: A single option can be chosen
 * - #weight (discouraged): Sets the weight of the skin inside the group; NULL
 *   by default.
 * - #stylesheets: A array containing information about stylesheet(s) the skin
 *   requires. This maps to the functionality of drupal_add_css() with one
 *   exception: paths are automatically assumed as relative to the plugin
 *   directory, unless external. Examples:
 *   - Simple:
 *       '#stylesheets' => array('css/skin-name.css')
 *     - Advanced: 
 *       '#stylesheets' => array(
 *         array('css/skin-name-ie.css', array(
 *           'media' => 'screen',
 *           'browsers' => array(
 *             'IE' => 'lte IE 8'
 *            ),
 *          ),
 *       )
 * - #scripts: A array containing information about script(s) the skin
 *   requires. This maps to the functionality of drupal_add_js() with one
 *   exception: paths are automatically assumed as relative to the plugin
 *   directory, unless external. Examples:
 *   - Simple:
 *     '#scripts' => array('js/skin-name.js'),
 *   - Advanced: 
 *     #scripts' => array(
 *     array(
 *       'js/skin-name-advanced.js',
 *       array(
 *         'scope' => 'footer',
 *         'group' => JS_THEME,
 *       ),
 *     ),
 * - #options (required): An array containing one or more options (also arrays)
 *   for the user to choose from when applying skins. Each option key should be
 *   a machine name describing the option. An option should including the
 *   following keys:
 *   - #label: The option label.
 *   - #class: An array containing one or more classes the skin should apply. A
 *     single class may be entered as a string, but multiple classes should be
 *     entered as an array: For example:
 *     - Single:
 *       '#class' => 'class'
 *     - Multiple:
 *       '#class' => array('class-b', 'class-b') 
 *   - #stylesheets: Same as above, but applies to a specific option only.
 *   - #scripts: Same as above, but applies to a specific option only.
 * - #features: An array containing certain allowed hooks, which allow you to
 *   limit where the skin can be used. Allowed options include: block,
 *   block__MODULE, comment, comment__NODETYPE, comment_wrapper,
 *   comment__wrapper_NODETYPE, node, node__NODETYPE, region,
 *   region__REGIONNAME, panels_display, panels_region, panels_pane, views_view,
 *   views_view__STYLENAME, views_view__DISPLAY_NAME, views_view__VIEWNAME, and
 *   views_view__VIEWNAME_DISPLAYNAME.
 * - #default_status: Skins are disabled by default to keep UI clutter to a
 *   minimum. In some cases, like contrib themes, it makes sense to enable skins
 *   which are required to make the theme work properly by default. Setting this
 *   property to 1, will cause it to be enabled it by default.
 *
 * Programmatically added data:
 * - #status: An array containing each theme as the key and the status of the
 *   skin in it (0/1). These values override #default_status on a per theme
 *   basis. The "Manage skins" page only lists skins which are contained in an
 *   enabled theme or module. This setting is useful for sub-themes to override
 *   via an hook_skinr_skins_alter() to auto-enable skins located in a parent
 *   theme which may not be enabled.
 *   For example:
 *     '#status' => array(
 *       'theme_name' => 1,
 *      ),
 * - #source: An array containing the following information about the module or
 *   theme implementing the skin:
 *   - #type: Either module or theme.
 *   - #name: The name of the module or theme.
 *   - #plugin: The name of the plugin.
 *   - #path: The path to the skin's plugin directory.
 *
 * The "hook" prefix is substituted with the name of the module or theme
 * implementing it, followed by the plugin name, e.g.
 * THEMENAME_PLUGINNAME_skinr_skins(), or MODULENAME_PLUGINNAME_skinr_skins().
 *
 * @todo Document that support for #templates have been removed. The code does
 * not work properly and will eventually need an overhaul, so removing fluff.
 * @todo Document that collapsible/collapsed options are obsolete for groups in
 * the new version.
 * @todo A better name needs to be agreed upon for #features. This name is
 * confusing people to death, and doesn't accurately describe what it does.
 * @todo A helper function needs to be created for alter hooks to use to control
 * the status of a dependency skin.
 * 
 */
function skinr_styles_skinr_skins() {
  $skins['skinr_font'] = array(
    '#title' => t('Font family'),
    '#type' => 'select',
    '#group' => 'skinr_styles_typography',
    '#stylesheets' => array('css/typography.css'),
    '#options' => array(
      'font_1' => array(
        '#label' => t('Arial, Helvetica, Nimbus Sans L, Liberation Sans, FreeSans'),
        '#class' => 'font-1',
      ),
      'font_2' => array(
        '#label' => t('Lucida Grande, Lucida Sans Unicode, DejaVu Sans, Tahoma'),
        '#class' => 'font-2',
      ),
      'font_3' => array(
        '#label' => t('Geneva, Bitstream Vera Serif, Tahoma'),
        '#class' => 'font-3',
      ),
      'font_4' => array(
        '#label' => t('Georgia, Bitstream Vera Serif'),
        '#class' => 'font-4',
      ),
      'font_5' => array(
        '#label' => t('Tahoma, Geneva, DejaVu Sans Condensed'),
        '#class' => 'font-5',
      ),
      'font_6' => array(
        '#label' => t('Bitstream Vera Sans, Verdana, Arial'),
        '#class' => 'font-6',
      ),
      'font_7' => array(
        '#label' => t('Palatino Linotype, URW Palladio L, Book Antiqua, Palatino'),
        '#class' => 'font-7',
      ),
      'font_8' => array(
        '#label' => t('Free Serif, Times New Roman, Times'),
        '#class' => 'font-8',
      ),
    ),
  );
  $skins['skinr_font_size'] = array(
    '#title' => t('Font size'),
    '#type' => 'select',
    '#group' => 'skinr_styles_typography',
    '#stylesheets' => array('css/typography.css'),
    '#options' => array(
      'size_1' => array(
        '#label' => '0.846em (11px)',
        '#class' => 'size-1',
      ),
      'size_2' => array(
        '#label' => '0.923em (12px)',
        '#class' => 'size-2',
      ),
      'size_3' => array(
        '#label' => '1.077em (14px)',
        '#class' => 'size-3',
      ),
      'size_4' => array(
        '#label' => '1.231em (16px)',
        '#class' => 'size-4',
      ),
      'size_5' => array(
        '#label' => '1.385em (18px)',
        '#class' => 'size-5',
      ),
      'size_6' => array(
        '#label' => '1.538em (20px)',
        '#class' => 'size-6',
      ),
    ),
  );
  $skins['skinr_font_style'] = array(
    '#title' => t('Font style'),
    '#type' => 'radios',
    '#group' => 'skinr_styles_typography',
    '#stylesheets' => array('css/typography.css'),
    '#options' => array(
      'normal' => array(
        '#label' => t('Normal'),
        '#class' => 'fs-normal',
      ),
      'italic' => array(
        '#label' => t('Italic'),
        '#class' => 'fs-italic',
      ),
    ),
  );
  $skins['skinr_font_other'] = array(
    '#title' => t('Font weight'),
    '#group' => 'skinr_styles_typography',
    '#stylesheets' => array('css/typography.css'),
    '#options' => array(
      'bold' => array(
        '#label' => t('Bold'),
        '#class' => 'fs-bold',
      ),
      'small_caps' => array(
        '#label' => t('Normal'),
        '#class' => 'fv-smallcaps',
      ),
    ),
  );

  $skins['skinr_font_face'] = array(
    '#title' => t('Heading font family'),
    '#description' => t('Applies to headings level 1-3.'),
    '#group' => 'skinr_styles_typography',
    '#options' => array(
      'droid_sans' => array(
        '#label' => t('Droid Sans'),
        '#class' => array('ff', 'droid-sans'),
        '#stylesheets' => array('fonts/droid-sans/css/normal.css'),
      ),
      'droid_sans_bold' => array(
        '#label' => t('Droid Sans (bold)'),
        '#class' => array('ff', 'droid-sans-b'),
        '#stylesheets' => array('fonts/droid-sans/css/bold.css'),
      ),
      'fontin_sans' => array(
        '#label' => t('Fontin Sans'),
        '#class' => array('ff', 'fontin-sans'),
        '#stylesheets' => array('fonts/fontin-sans/css/regular.css'),
      ),
      'fontin_sans_bold' => array(
        '#label' => t('Fontin Sans (bold)'),
        '#class' => array('ff', 'fontin-sans-b'),
        '#stylesheets' => array('fonts/fontin-sans/css/bold.css'),
      ),
      'museo_300' => array(
        '#label' => t('Museo (300)'),
        '#class' => array('ff', 'museo-300'),
        '#stylesheets' => array('fonts/museo/css/300.css'),
      ),
      'museo_500' => array(
        '#label' => t('Museo (500)'),
        '#class' => array('ff', 'museo-500'),
        '#stylesheets' => array('fonts/museo/css/500.css'),
      ),
      'museo_700' => array(
        '#label' => t('Museo (700)'),
        '#class' => array('ff', 'museo-700'),
        '#stylesheets' => array('fonts/museo/css/700.css'),
      ),
    ),
  );

  return $skins;
}
