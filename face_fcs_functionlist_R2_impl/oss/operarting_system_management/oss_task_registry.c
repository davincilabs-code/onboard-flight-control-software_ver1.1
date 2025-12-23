#include "oss_kernel.h"
#include "face_log.h"

#include "pcs/flight_management/flight_mode_management.h"
#include "pcs/flight_management/rc_flight_mode_management.h"
#include "pcs/flight_management/pilot_flight_mode_management.h"
#include "pcs/flight_management/auto_flight_mode_management.h"
#include "pcs/flight_management/take_off_mode.h"
#include "pcs/flight_management/landing_mode.h"
#include "pcs/flight_management/hovering_mode.h"
#include "pcs/flight_management/rotating_mode.h"
#include "pcs/flight_management/return_to_home_mode.h"
#include "pcs/flight_management/emergency_landing_mode.h"
#include "pcs/flight_management/point_to_point_flight_mode.h"
#include "pcs/flight_management/auto_flight_mode_wp_mode.h"
#include "pcs/flight_management/flight_status_management.h"
#include "pcs/flight_management/flight_alarm_management.h"
#include "pcs/flight_management/fault_detection_and_isolation.h"
#include "pcs/guidance_and_navigation_management/path_planning_and_tracking.h"
#include "pcs/guidance_and_navigation_management/taget_posture_generator.h"
#include "pcs/guidance_and_navigation_management/sensor_fusion.h"
#include "pcs/guidance_and_navigation_management/current_posture_estimator.h"
#include "pcs/guidance_and_navigation_management/collision_avoidance_management.h"
#include "pcs/fcl_management/flight_control_law_management.h"
#include "pcs/fcl_management/lift_mode_controller.h"
#include "psss/i_o_processing_management/io_management.h"
#include "psss/i_o_processing_management/analog_input_data_processing.h"
#include "psss/i_o_processing_management/digitla_input_data_processing.h"
#include "psss/i_o_processing_management/analog_output_data_processing.h"
#include "psss/i_o_processing_management/digitla_output_data_processing.h"
#include "ioss/sensor_data_management/air_data_sensor.h"
#include "ioss/sensor_data_management/gps_sensor.h"
#include "ioss/sensor_data_management/ralt_sensor.h"
#include "ioss/sensor_data_management/ahrs_sensor.h"
#include "ioss/actuator_control_management/lift_actuator_controller.h"
#include "psss/communication_management/serial_communication_manager.h"
#include "psss/communication_management/can_communication_manager.h"
#include "psss/communication_management/ethernet_communication_manager.h"
#include "psss/communication_management/wifi_lte_communication_manager.h"
#include "psss/communication_management/rf_vhf_communication_manager.h"
#include "psss/communication_management/rc_communication_manager.h"
#include "psss/battery_management/battery_management.h"
#include "psss/battery_management/battery_status_manager.h"
#include "psss/battery_management/battery_alarm_manager.h"
#include "psss/engine_management/engine_mode_management.h"
#include "psss/engine_management/engine_status_manager.h"
#include "psss/engine_management/engine_alarm_manager.h"
#include "psss/system_management/flight_data_manager.h"
#include "psss/system_management/sytem_configuration_manager.h"
#include "psss/system_management/power_energy_manager.h"
#include "psss/system_management/fcc_manager.h"
#include "psss/system_management/sensor_manager.h"
#include "psss/system_management/actuator_manager.h"
#include "psss/system_management/health_fault_manager.h"
#include "psss/system_management/wow_landingger_manager.h"
#include "psss/system_management/mfp_manager.h"
#include "psss/system_management/gcs_manager.h"
#include "psss/system_management/side_stick_manager.h"
#include "ioss/operarting_system_management/device_driver_manager.h"

void oss_register_all_tasks(void)
{
    face_log_info("OSS: registering tasks from FunctionList R2");
    (void)oss_kernel_add_task("PCS:Flight Mode Management", pcs_flight_management_flight_mode_management_step, 20000u, 25);
    (void)oss_kernel_add_task("PCS:RC Flight Mode Management", pcs_flight_management_rc_flight_mode_management_step, 20000u, 25);
    (void)oss_kernel_add_task("PCS:Pilot Flight Mode Management", pcs_flight_management_pilot_flight_mode_management_step, 20000u, 25);
    (void)oss_kernel_add_task("PCS:Auto Flight Mode Management", pcs_flight_management_auto_flight_mode_management_step, 20000u, 25);
    (void)oss_kernel_add_task("PCS:Take Off Mode", pcs_flight_management_take_off_mode_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Landing Mode", pcs_flight_management_landing_mode_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Hovering Mode", pcs_flight_management_hovering_mode_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Rotating Mode", pcs_flight_management_rotating_mode_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Return to Home Mode", pcs_flight_management_return_to_home_mode_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Emergency Landing Mode", pcs_flight_management_emergency_landing_mode_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Point to Point Flight Mode", pcs_flight_management_point_to_point_flight_mode_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Auto Flight Mode(WP Mode)", pcs_flight_management_auto_flight_mode_wp_mode_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Flight Status Management", pcs_flight_management_flight_status_management_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Flight Alarm Management", pcs_flight_management_flight_alarm_management_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Fault Detection & Isolation", pcs_flight_management_fault_detection_and_isolation_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Path Planning & Tracking", pcs_guidance_and_navigation_management_path_planning_and_tracking_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Taget Posture Generator", pcs_guidance_and_navigation_management_taget_posture_generator_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Sensor Fusion", pcs_guidance_and_navigation_management_sensor_fusion_step, 10000u, 30);
    (void)oss_kernel_add_task("PCS:Current Posture Estimator", pcs_guidance_and_navigation_management_current_posture_estimator_step, 10000u, 30);
    (void)oss_kernel_add_task("PCS:Collision Avoidance Management", pcs_guidance_and_navigation_management_collision_avoidance_management_step, 20000u, 30);
    (void)oss_kernel_add_task("PCS:Flight Control Law Management", pcs_fcl_management_flight_control_law_management_step, 20000u, 20);
    (void)oss_kernel_add_task("PCS:Lift Mode Controller", pcs_fcl_management_lift_mode_controller_step, 10000u, 20);
    (void)oss_kernel_add_task("PSSS:IO Management", psss_i_o_processing_management_io_management_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Analog Input Data Processing", psss_i_o_processing_management_analog_input_data_processing_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Digitla Input Data Processing", psss_i_o_processing_management_digitla_input_data_processing_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Analog Output Data Processing", psss_i_o_processing_management_analog_output_data_processing_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Digitla Output Data Processing", psss_i_o_processing_management_digitla_output_data_processing_step, 50000u, 40);
    (void)oss_kernel_add_task("IOSS:Air Data Sensor ", ioss_sensor_data_management_air_data_sensor_step, 10000u, 10);
    (void)oss_kernel_add_task("IOSS:GPS Sensor", ioss_sensor_data_management_gps_sensor_step, 10000u, 10);
    (void)oss_kernel_add_task("IOSS:RALT Sensor", ioss_sensor_data_management_ralt_sensor_step, 10000u, 10);
    (void)oss_kernel_add_task("IOSS:AHRS Sensor", ioss_sensor_data_management_ahrs_sensor_step, 10000u, 10);
    (void)oss_kernel_add_task("IOSS:Lift Actuator Controller", ioss_actuator_control_management_lift_actuator_controller_step, 10000u, 10);
    (void)oss_kernel_add_task("PSSS:Serial Communication Manager", psss_communication_management_serial_communication_manager_step, 20000u, 15);
    (void)oss_kernel_add_task("PSSS:CAN Communication Manager", psss_communication_management_can_communication_manager_step, 20000u, 15);
    (void)oss_kernel_add_task("PSSS:EtherNet Communication Manager", psss_communication_management_ethernet_communication_manager_step, 20000u, 15);
    (void)oss_kernel_add_task("PSSS:Wifi(LTE) Communication Manager", psss_communication_management_wifi_lte_communication_manager_step, 20000u, 15);
    (void)oss_kernel_add_task("PSSS:RF(VHF) Communication Manager", psss_communication_management_rf_vhf_communication_manager_step, 20000u, 15);
    (void)oss_kernel_add_task("PSSS:RC Communication Manager", psss_communication_management_rc_communication_manager_step, 20000u, 15);
    (void)oss_kernel_add_task("PSSS:Battery Management ", psss_battery_management_battery_management_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Battery Status Manager", psss_battery_management_battery_status_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Battery Alarm Manager", psss_battery_management_battery_alarm_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Engine Mode Management", psss_engine_management_engine_mode_management_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Engine Status Manager", psss_engine_management_engine_status_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Engine Alarm Manager", psss_engine_management_engine_alarm_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Flight Data Manager", psss_system_management_flight_data_manager_step, 100000u, 40);
    (void)oss_kernel_add_task("PSSS:Sytem Configuration Manager", psss_system_management_sytem_configuration_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Power(Energy) Manager", psss_system_management_power_energy_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:FCC Manager", psss_system_management_fcc_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Sensor Manager", psss_system_management_sensor_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Actuator Manager", psss_system_management_actuator_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Health/Fault Manager", psss_system_management_health_fault_manager_step, 50000u, 18);
    (void)oss_kernel_add_task("PSSS:WOW/LandingGer Manager", psss_system_management_wow_landingger_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:MFP Manager", psss_system_management_mfp_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:GCS Manager", psss_system_management_gcs_manager_step, 50000u, 40);
    (void)oss_kernel_add_task("PSSS:Side Stick Manager", psss_system_management_side_stick_manager_step, 20000u, 40);
    (void)oss_kernel_add_task("IOSS:Device Driver Manager", ioss_operarting_system_management_device_driver_manager_step, 10000u, 10);
}
