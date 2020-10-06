<?php 

module_load_include('inc', 'pp_contact', 'inc/pp_announcement_functions');

function _pp_announcement_create_ajax_callback($ajax) {	
	
	if ($ajax) {
	
		ctools_include('ajax');
		ctools_include('modal');
	
		$form_state = array(
			'ajax' => TRUE,
			'title' => '<h5 class="pi-weight-700 pi-uppercase pi-letter-spacing no-margin-bottom"> '.drupal_get_title().'</h5>',
		);
	
		// Use ctools to generate ajax instructions for the browser to create
		// a form in a modal popup.
		$output = ctools_modal_form_wrapper('_pp_announcement_create_form', $form_state);
	
		// If the form has been submitted, there may be additional instructions
		// such as dismissing the modal popup.
		if (!empty($form_state['ajax_commands'])) {
			$output = $form_state['ajax_commands'];
		}
	
		// Return the ajax instructions to the browser via ajax_render().
		print ajax_render($output);
		drupal_exit();
	}
	else {
		return drupal_get_form('_pp_announcement_create_form');
	}
}

function _pp_announcement_create_form($form, &$form_state) {

	//TODO DB Select users to test sending the announcement to them 

	//Content / Body 
	//Experation date 


	$weight = 0;

	// content wrapper for ctools modal
	$form['#prefix'] = '<div class="pi-section-white pi-section-w">';
	$form['#suffix'] = '</div>';
	
	$form['fieldset_announcement_content'] = array(
		'#type' => 'textarea',
		'#title' => t('Content body for formal announcement'),
		'#attributes' => array(
			'placeholder' => t('Content'),
		),
		'#cols' => 30,
		'#weight' => $weight++,
		'#rows' => 3,
		'#required' => TRUE,
		'#prefix' => '<div class="col-xs-6 col-sm-4 col-md-4">',
		'#suffix' => '</div>',
	);

	return $form;

}
