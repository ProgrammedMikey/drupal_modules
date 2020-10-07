<?php 

module_load_include('inc', 'pp_announcement', 'inc/pp_announcement_functions');


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

	//Expiration date?
	$weight = 0;

	// content wrapper for ctools modal
	$form['#prefix'] = '<div class="pi-section-white pi-section-w">';
	$form['#suffix'] = '</div>';
	
	$form['fieldset_announcement_content'] = array(
		'#type' => 'textarea',
		'#title' => t('Formal Announcement'),
		'#attributes' => array(
			'placeholder' => t('Content body for formal announcement'),
		),
		'#cols' => 30,
		'#weight' => $weight++,
		'#rows' => 3,
		'#required' => TRUE,
		'#prefix' => '<div class="col-xs-6 col-sm-4 col-md-4">',
		'#suffix' => '</div>',
	);

		// address 1
		$form['fieldset_announcement_url'] = array(
			'#type' => 'textfield',
			'#title' => t('Announcement URL'),
			'#attributes' => array(
				'placeholder' => t('url'),
			),
			'#size' => 10,
			'#weight' => $weight++,
			'#maxlength' => 50,
			'#required' => FALSE,
			'#prefix' => '<div class="col-xs-6 col-sm-4 col-md-4">',
			'#suffix' => '</div>',
		);

		$form['fieldset_announcement_expiration_datetime'] = array(
			'#title' => t('Expiration date'),
			'#type' => 'date',
			'#description' => t('Select an expiration date'),
			'#default_value' => array(
			  'month' => format_date(time(), 'custom', 'n'), 
			  'day' => format_date(time(), 'custom', 'j'), 
			  'year' => format_date(time(), 'custom', 'Y'),
			),
		  );

		  	// ajax
	if( arg(5) == "ajax" ) {

		// fieldset submit - cancel
		$form['fieldset_submit_cancel'] = array(
			'#type' => 'fieldset',
			'#title' => '',
			'#weight' => 70,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#prefix' => '<div class="row pi-padding-top-20">',
			'#suffix' => '</div>',
		);
			// submit
			$form['fieldset_submit_cancel']['submit'] = array(
			'#type' => 'submit',
			'#weight' => 70,
			'#value' => t('Save announcement'),
			'#attributes' => array(
				'class' => array('btn pi-btn-blue'),
			),
			'#prefix' => '<div class="col-sm-6">',
			'#suffix' => '</div>',
		);
	}
	// form page
	else {
		
		// fieldset submit - cancel
		$form['fieldset_submit_cancel'] = array(
			'#type' => 'fieldset',
			'#title' => '',
			'#weight' => 70,
			'#collapsible' => FALSE,
			'#collapsed' => FALSE,
			'#prefix' => '<div class="row pi-padding-top-20">',
			'#suffix' => '</div>',
		);
			// submit
			$form['fieldset_submit_cancel']['submit_button'] = array(
				'#type' => 'submit',
				'#weight' => $weight++,
				'#value' => t('Save announcement'),
				'#attributes' => array(
					'class' => array('btn pi-btn-blue'),
				),
				'#prefix' => '<div class="col-sm-6">',
				'#suffix' => '</div>',
			);
			// cancel
			$form['fieldset_submit_cancel']['cancel_button'] = array(
				'#type' => 'button',
				'#name' => 'cancel',
				'#button_type' => 'button',
				'#value' => t('Cancel'),
				'#weight' => $weight++,
				'#attributes' => array(
					'class' => array('btn pi-btn-dark pi-btn-small'),
					'onClick' => 'location.replace("/"); return false;',
				),
				'#prefix' => '<div class="col-sm-6 pi-text-right">',
				'#suffix' => '</div>',
			);
	}	

	// required [markup]
	$form['field_announcement_required_fields'] = array(
		'#markup' => '
			<div class="pi-padding-top-20">
				<p class="pi-smaller-text">'.t('*required fields').'</p>
			</div>',
		'#weight' => 80,
	);

	return $form;
}

function _pp_announcement_create_form_submit ($form, &$form_state) {

	$fe_id = db_insert('pp_announcement')
	    ->fields(array(
			'pp_announcement_content' => $formstate['values']['fieldset_announcement_content'],
			'pp_announcement_url' => $formstate['values']['fieldset_announcement_url'],
			'pp_announcement_expiration_datetime' => $formstate['values']['fieldset_announcement_expiration_datetime']
		))
		->execute(); 
     drupal_set_message(t('Your announcement entry has been submitted'));
}
