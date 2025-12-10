import os
from glob import glob
from setuptools import setup

package_name = 'interactive_geometry'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        (os.path.join('share', package_name), ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*')),
        (os.path.join('share', package_name, 'rviz'), ['rviz/config.rviz']),
        (os.path.join('share', package_name, 'config'), ['config/ellipsoid_params.yaml'])
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    scripts=[
        'scripts/ellipsoid_generator',
        'src/interactive_ellipsoid_server_node',
        'src/interactive_ellipsoid_node'
    ],
    package_dir={"":"src"},
)
