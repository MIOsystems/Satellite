   M S B A M L   `   `   `  ���� P  LSatelliteConfigurator, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null=#clr-namespace:SatelliteConfiguratorSatelliteConfigurator  &     SatelliteConfigurator.MainWindow   U QScottPlot.WPF, Version=4.1.61.0, Culture=neutral, PublicKeyToken=e53b06131e34a3aaR NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5local#clr-namespace:SatelliteConfigurator     -     � Title$  SatelliteConfigurator��$
��1280��$	��720��.��� -    �Name$ grd_Grid�� � ColumnDefinitions �� �� �� ��  � RowDefinitions �� $��25 ��� �� �� $	��150 �.+��� $��Receive Log:��$��0��$��0��$��2��$��1���� $��Transmit Log:��$��1��$��0��$��2��$��1���� -    ��Name$ txb_ReceiveLog�� �� 
IsReadOnly .  �� AcceptsReturn .  �� TextWrapping$
 Wrap=�$��0��$��1��$��1��$��2��$��5,5,5,5q��� -   $ txb_TransmitLog�� .  . $
 Wrap=�$��1��$��1��$��1��$��2��$��5,5,5,5q��� $��0��$��3��$��2��$��1��$
��Left=�$	��Top=�.+�� $
��Left=�$	��Top=�$��5,5,5,5q�.+��� $��Port:���� -    ��Name$ cmb_ComPorts��$	��200���� -   	 ��Name$	 btn_OpenPort��$��	Open port��$	��100��$��25���� -   $	 btn_ClosePort��$��
Close port��$	��100��$��25��{�.  �� -   $	 btn_RefreshPorts��$��Refresh ports��$	��100��$��25��$
��Left=�$	��Top=�$��5,5,5,5q��� $��2��$��3��$��1��$��1��$
��Left=�$	��Top=�.+��� 
 �� Orientation$
 
Horizontal=�.+��� -	   $	 btn_Transmit��$��Transmit Configuration��$	��200��$��25��$��5,5,5,5q�{�.  $
��Left=�$	��Top=�� $	��300��$	��100�� �� $��20 ��� �� $��20 ���  �� �� �� �� .+��� $��Acceleration��$��0��$��0��$��2��$��1���� $��x:��$��0��$��1��$��1��$��1���� -
    ��Name$ 
lbl_accelX��$��1��$��1��$��1��$��1���� $��y:��$��0��$��2��$��1��$��1���� -   $ 
lbl_accelY��$��1��$��2��$��1��$��1���� $��z:��$��0��$��3��$��1��$��1���� -   $ 
lbl_accelZ��$��1��$��3��$��1��$��1���� $
��Gyro��$��2��$��0��$��2��$��1���� $��x:��$��2��$��1��$��1��$��1���� -   $ 	lbl_gyroX��$��3��$��1��$��1��$��1���� $��y:��$��2��$��2��$��1��$��1���� -   $ 	lbl_gyroY��$��3��$��2��$��1��$��1���� $��z:��$��2��$��3��$��1��$��1���� -   $ 	lbl_gyroZ��$��3��$��3��$��1��$��1���� $��3��$��3��$��1��$��1��$
��Left=�$	��Top=�.+��� $��Chip:���� -   $ cmb_Chip��$	��150�� �� SelectedIndex$ 0���� $��	Register:���� -   $ cmb_Register��$	��150���� $��Value:���� -   $ 	cmb_Value��$	��150��