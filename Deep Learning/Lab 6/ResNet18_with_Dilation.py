from tensorflow.keras import layers, models

def identity_block(x, filters, kernel_size=3, stride=1, dilation_rate=1):
    x_skip = x

    x = layers.Conv2D(filters, kernel_size=1, strides=stride, padding='same')(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.Conv2D(filters, kernel_size, strides=1, padding='same', dilation_rate=dilation_rate)(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.add([x, x_skip])
    x = layers.Activation('relu')(x)
    return x

def dilated_convolutional_block(x, filters, kernel_size=3, stride=1, dilation_rate=2):
    x_skip = x

    x = layers.Conv2D(filters, kernel_size=1, strides=stride, padding='same')(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x = layers.Conv2D(filters, kernel_size, strides=1, padding='same', dilation_rate=dilation_rate)(x)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)

    x_skip = layers.Conv2D(filters, kernel_size=1, strides=stride, padding='same')(x_skip)
    x_skip = layers.BatchNormalization()(x_skip)

    x = layers.add([x, x_skip])
    x = layers.Activation('relu')(x)
    return x

def ResNet18_With_Dilation(inputShape=(224,224,3), num_classes=8):
    input_layer = layers.Input(shape=inputShape)

    x = layers.Conv2D(64, 7, strides=2, padding='same')(input_layer)
    x = layers.BatchNormalization()(x)
    x = layers.Activation('relu')(x)
    x = layers.MaxPooling2D(3, strides=2, padding='same')(x)

    x = dilated_convolutional_block(x, filters=64, kernel_size=3, stride=1)
    x = identity_block(x, filters=64, kernel_size=3)

    x = dilated_convolutional_block(x, filters=128, kernel_size=3, stride=1)
    x = identity_block(x, filters=128, kernel_size=3)

    x = dilated_convolutional_block(x, filters=256, kernel_size=3, stride=1)
    x = identity_block(x, filters=256, kernel_size=3)

    x = dilated_convolutional_block(x, filters=512, kernel_size=3, stride=1)
    x = identity_block(x, filters=512, kernel_size=3)

    x = layers.GlobalAveragePooling2D()(x)
    x = layers.Dense(num_classes, activation='softmax')(x)

    model = models.Model(inputs=input_layer, outputs=x, name='resnet18')
    return model